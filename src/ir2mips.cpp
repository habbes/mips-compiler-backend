#include "ir2mips.h"
#include "mips_reg.h"
#include <string>
#include <typeinfo>
#include "naive_reg_allocator.h"

using mips::MipsInstruction;
using mips::MipsSymbol;

Ir2Mips::Ir2Mips (IrProgram & ir, BaseRegAllocator & regAllocator)
    : ir_(ir), instIndex_(0), funcIndex_(0), regAllocator_(regAllocator)
{
}

const mips::MipsProgram &Ir2Mips::mips() const
{
    return mips_;
}

mips::MipsProgram &Ir2Mips::translate()
{
    injectProgramStart();

    for (int i = 0; i < ir_.numFunctions(); i++)
    {
        funcIndex_ = i;
        translateNextFunction();
    }

    injectBuiltInFunctions();

    return mips_;
}

void Ir2Mips::translateNextFunction()
{
    auto & irFunc = ir_[funcIndex_];
    mips_.newFunction(irFunc);
    if (curFuncRegAllocator_)
    {
        curFuncRegAllocator_.reset();
    }
    curFuncRegAllocator_ = regAllocator_.getFunctionAllocator(irFunc);
    instIndex_ = -1;
    if (curMipsFunction().backsUpRa())
    {
        curMipsFunction().addCodeComment("backup return address");
        // backup $ra
        // sw $ra, func_saved_ra
        emitStore(MipsSymbol::makeReg(mips::REG_RA), curMipsFunction().backupRaVar());
    }

    if (!isMainOrBuiltinFunction())
    {
        backupPersistentRegs();
    }

    // load params
    curMipsFunction().addCodeComment("load function arguments");
    std::string argsRegs[] = { mips::REG_A0, mips::REG_A1, mips::REG_A2, mips::REG_A3 };
    int i = 0;
    for (auto & param : irFunc.params())
    {
        // currently only support up to 4 params
        if (i >= 4) break;
        emitStore(MipsSymbol::makeReg(argsRegs[i]), irToMipsSymbol(param, true));
        i++;
    }

    instIndex_ = 0;
    while (instIndex_ < irFunc.numInstructions())
    {
        curFuncRegAllocator_->beforeInstruction(*this, instIndex_);
        translateNextInstruction();
        curFuncRegAllocator_->afterInstruction(*this, instIndex_);
        instIndex_++;
    }
}

const IrInstruction &Ir2Mips::nextIrInstruction()
{
    auto & irFunc = ir_[funcIndex_];
    auto & inst = irFunc.instruction(instIndex_);
    return inst;
}

const IrFunction &Ir2Mips::curIrFunction()
{
    return ir_[funcIndex_];
}

mips::MipsFunction & Ir2Mips::curMipsFunction ()
{
    return mips_.currentFunction();
}

MipsSymbol Ir2Mips::irToMipsSymbol (const SymbolInfo &irSym, bool isDef)
{
    if (irSym.type == SymbolType::CONST)
    {
        return MipsSymbol::makeConst(irSym.intValue);
    }
    if (irSym.type == SymbolType::TARGET_LABEL)
    {
        return MipsSymbol::makeLabel(irSym.name);
    }
    // a variable is the only other type of symbol we care about translating
    auto var = curMipsFunction().vars().at(irSym.name);
    return curFuncRegAllocator_->getRegIfAllocated(var, instIndex_, isDef);
}

void Ir2Mips::emit (mips::MipsInstruction inst)
{
    curMipsFunction().addInstruction(std::move(inst));
}

void Ir2Mips::emitLoad (const mips::MipsSymbol & src, const mips::MipsSymbol & dest)
{
    if (src.type == mips::MipsSymbolType::CONST)
    {
        emit({ mips::MipsOp::LI, { dest, src } });
    }
    else if (src.type == mips::MipsSymbolType::VAR && src.size == mips::MipsSymbolSize::SPACE)
    {
        // load array address
        emit({ mips::MipsOp::LA, { dest, src } });
    }
    else if (src.type == mips::MipsSymbolType::REG)
    {
        // move data between registers
        emit({ mips::MipsOp::MOVE, { dest, src } });
    }
    else
    {
        // load var
        emit({ mips::MipsOp::LW, { dest, src } });
    }
}

void Ir2Mips::emitStore (const mips::MipsSymbol & src, const mips::MipsSymbol & dest)
{
    if (dest.type == mips::MipsSymbolType::REG)
    {
        emit({ mips::MipsOp::MOVE, { dest, src } });
    }
    else
    {
        // load var
        emit({ mips::MipsOp::SW, { src, dest } });
    }
}

void Ir2Mips::translateNextInstruction()
{
    auto & inst = nextIrInstruction();
    curMipsFunction().addCodeComment(std::to_string(instIndex_) + ": " + inst.toString());

    switch (inst.op)
    {
        case OpCode::ASSIGN:
            translateAssign(inst);
            break;
        case OpCode::LABEL:
            translateLabel(inst);
            break;
        case OpCode::ADD:
        case OpCode::MULT:
        case OpCode::SUB:
        case OpCode::DIV:
        case OpCode::OR:
        case OpCode::AND:
            translateBinary(inst);
            break;
        case OpCode::BREQ:
        case OpCode::BRNEQ:
        case OpCode::BRLT:
        case OpCode::BRLEQ:
        case OpCode::BRGT:
        case OpCode::BRGEQ:
            translateConditionalBranch(inst);
            break;
        case OpCode::GOTO:
            translateGoto(inst);
            break;
        case OpCode::CALL:
        case OpCode::CALLR:
            translateCall(inst);
            break;
        case OpCode::ARRAY_STORE:
            translateArrayStore(inst);
            break;
        case OpCode::ARRAY_LOAD:
            translateArrayLoad(inst);
            break;
        case OpCode::RETURN:
            translateReturn(inst);
            break;
        case OpCode::INVALID:
            emit({ mips::MipsOp::INVALID });
    }
}

void Ir2Mips::translateLabel(const IrInstruction &inst)
{
    auto & irLabel = inst.params[0];
    auto mipsLabel = MipsSymbol::makeLabel(irLabel.name);

    emit({ mips::MipsOp::INST_LABEL, { mipsLabel } });
}

void Ir2Mips::translateAssign(const IrInstruction &inst)
{
    if (inst.params[0].isArray)
    {
        // assigning an array
        // translate into a function call to initIntArray
        // from: assign, array, size, value
        // to: call, initIntArray, array, size, value
        auto arrayStoreInst = IrInstructionBuilder::fromOp(OpCode::CALL)
            .param({ "initIntArray", SymbolType::FUNC })
            .param(inst.params[0])
            .param(inst.params[1])
            .param(inst.params[2])
            .build();
        
        translateCall(*arrayStoreInst);
        return;
    }


    auto & irDest = inst.params[0];
    auto & irSrc = inst.params[1];
    MipsSymbol t8 = MipsSymbol::makeReg(mips::REG_T8);
    auto & mipsDestVar = curMipsFunction().vars().at(irDest.name);
    auto mipsDest = curFuncRegAllocator_->getRegIfAllocated(mipsDestVar, instIndex_, true);

    if (mipsDest.isReg())
    {
        emitLoad(irToMipsSymbol(irSrc), mipsDest);
    }
    else
    {
        emitLoad(irToMipsSymbol(irSrc), t8);
        emitStore(t8, mipsDest);
    }
    
}

void Ir2Mips::translateBinary(const IrInstruction &inst)
{
    auto & irLeft = inst.params[0];
    auto & irRight = inst.params[1];
    auto & irDest = inst.params[2];
    auto t8 = MipsSymbol::makeReg(mips::REG_T8);
    auto t9 = MipsSymbol::makeReg(mips::REG_T9);
    auto mipsDest = irToMipsSymbol(irDest, true);

    auto left = irToMipsSymbol(irLeft);
    auto right = irToMipsSymbol(irRight);
    MipsSymbol mipsLeft, mipsRight;

    if (left.isReg())
    {
        mipsLeft = left;
    }
    else
    {
        emitLoad(left, t8);
        mipsLeft = t8;
    }

    if (right.isReg())
    {
        mipsRight = right;
    }
    else
    {
        emitLoad(right, t9);
        mipsRight = t9;
    }
    
    mips::MipsOp op =
        inst.op == OpCode::ADD ? mips::ADD :
        inst.op == OpCode::SUB ? mips::SUB :
        inst.op == OpCode::MULT ? mips::MUL :
        inst.op == OpCode::DIV ? mips::DIV :
        inst.op == OpCode::AND ? mips::AND :
        inst.op == OpCode::OR ? mips::OR :
        mips::INVALID;
    
    if (mipsDest.isReg())
    {
        emit({ op, { mipsDest, mipsLeft, mipsRight } });
    }
    else
    {
        emit({ op, { t8, mipsLeft, mipsRight } });
        emitStore(t8, mipsDest);
    }
}

void Ir2Mips::translateConditionalBranch(const IrInstruction &inst)
{
    auto & irLeft = inst.params[0];
    auto & irRight = inst.params[1];
    auto & irLabel = inst.params[2];
    auto t8 = MipsSymbol::makeReg(mips::REG_T8);
    auto t9 = MipsSymbol::makeReg(mips::REG_T9);
    auto mipsLabel = irToMipsSymbol(irLabel);

    auto left = irToMipsSymbol(irLeft);
    auto right = irToMipsSymbol(irRight);
    MipsSymbol mipsLeft, mipsRight;

    if (left.isReg())
    {
        mipsLeft = left;
    }
    else
    {
        emitLoad(left, t8);
        mipsLeft = t8;
    }

    if (right.isReg())
    {
        mipsRight = right;
    }
    else
    {
        emitLoad(right, t9);
        mipsRight = t9;
    }
    
    mips::MipsOp op =
        inst.op == OpCode::BREQ ? mips::BEQ :
        inst.op == OpCode::BRNEQ ? mips::BNE :
        inst.op == OpCode::BRLT ? mips::BLT :
        inst.op == OpCode::BRLEQ ? mips::BLE :
        inst.op == OpCode::BRGT ? mips::BGT :
        inst.op == OpCode::BRGEQ ? mips::BGE :
        mips::INVALID;
    emit({ op, { mipsLeft, mipsRight, mipsLabel }});
}

void Ir2Mips::translateGoto (const IrInstruction &inst)
{
    emit({ mips::MipsOp::J, { irToMipsSymbol(inst.label()) } });
}

void Ir2Mips::translateCall(const IrInstruction &inst)
{
    // assume up to 4 args
    // TODO add support for 4+ args, store additional args in vars or registers or stack
    std::string regs[] = { mips::REG_A0, mips::REG_A1, mips::REG_A2, mips::REG_A3 };
    auto it = inst.funcArgsBegin();
    for (int i = 0; i < inst.funcArgsCount(); i++)
    {
        emitLoad(irToMipsSymbol(*(it + i)), MipsSymbol::makeReg(regs[i]));
    }

    emit({ mips::MipsOp::JAL, { MipsSymbol::makeLabel(inst.label().name) } });

    if (inst.hasReturnValue())
    {
        // store return value from $v0
        emitStore(MipsSymbol::makeReg(mips::REG_V0), irToMipsSymbol(inst.returnValue(), true));
    }
}

void Ir2Mips::translateArrayStore(const IrInstruction &inst)
{
    // translate into a function call to storeIntArray
    // from: array_store, array, index, value
    // to: call, storeIntArray, array, index, value
    auto arrayStoreInst = IrInstructionBuilder::fromOp(OpCode::CALL)
        .param({ "storeIntArray", SymbolType::FUNC })
        .param(inst.params[0])
        .param(inst.params[1])
        .param(inst.params[2])
        .build();

    translateCall(*arrayStoreInst);
}

void Ir2Mips::translateArrayLoad(const IrInstruction &inst)
{
    // transform into a function call to built-in loadIntArray
    // from: array_load, value, array, index
    // to: callr,  value, loadIntArray, array, index
    auto arrayLoadInst = IrInstructionBuilder::fromOp(OpCode::CALLR)
        .param(inst.params[0])
        .param({ "loadIntArray", SymbolType::FUNC })
        .param(inst.params[1])
        .param(inst.params[2])
        .build();

    translateCall(*arrayLoadInst);
}

void Ir2Mips::translateReturn (const IrInstruction &inst)
{
    if (inst.hasReturnValue())
    {
        emitLoad(irToMipsSymbol(inst.returnValue()), MipsSymbol::makeReg(mips::REG_V0));
    }

    if (curMipsFunction().backsUpRa())
    {
        // restore $ra from backup: lw $ra, func_saved_ra
        emitLoad(curMipsFunction().backupRaVar(), MipsSymbol::makeReg(mips::REG_RA));
    }

    if (!isMainOrBuiltinFunction())
    {
        restorePersistentRegs();
    }

    emit({ mips::MipsOp::JR, { MipsSymbol::makeReg(mips::REG_RA) } });
}

void Ir2Mips::injectBuiltInFunctions ()
{
    injectPrintiFunction();
    injectStoreIntArray();
    injectLoadIntArray();
    injectInitIntArray();
    injectExitFunction();
}

void Ir2Mips::injectPrintiFunction ()
{
    /*
    printi:
    .data
    lf:	.asciiz	"\n"
    .text
    li	$v0, 1
    syscall
    li	$v0,4
    la	$a0, lf
    syscall
    jr	$ra
    */

    mips_.newFunction("printi");
    curMipsFunction().addVar(MipsSymbol::makeVar("printi_lf", mips::MipsSymbolSize::ASCIIZ), "\n");
    emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_V0), MipsSymbol::makeConst(1) } } });
    emit({ mips::MipsOp::SYSCALL });
    emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_V0), MipsSymbol::makeConst(4) } } });
    emit({ mips::MipsOp::LA, { { MipsSymbol::makeReg(mips::REG_A0), curMipsFunction().vars().at("printi_lf") } } });
    emit({ mips::MipsOp::SYSCALL });
    emit({ mips::MipsOp::JR, { { MipsSymbol::makeReg(mips::REG_RA) } } });
}

void Ir2Mips::injectStoreIntArray ()
{
    /*
    storeIntArray:
	# $a0=address of array, $a1 = index, $a2 = value
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	sw $a2, ($a0)
	jr $ra
    */

   mips_.newFunction("storeIntArray");
   emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeConst(4) } } });
   emit({ mips::MipsOp::MUL, { { MipsSymbol::makeReg(mips::REG_T9), MipsSymbol::makeReg(mips::REG_A1), MipsSymbol::makeReg(mips::REG_T8) } } });
   emit({ mips::MipsOp::ADD, { { MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeReg(mips::REG_T9) } } });
   emit({ mips::MipsOp::SW, { { MipsSymbol::makeReg(mips::REG_A2), MipsSymbol::makeAddressReg(mips::REG_A0) } } });
   emit({ mips::MipsOp::JR, { { MipsSymbol::makeReg(mips::REG_RA) } } });
}

void Ir2Mips::injectLoadIntArray ()
{
    /*
    loadIntArray:
	# $a0=address of array, $a1 = index
	li $s0, 4
	mul $s1, $a1, $s0
	add $a0, $a0, $s1
	lw $v0, ($a0)
	jr $ra
    */

   mips_.newFunction("loadIntArray");
   emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeConst(4) } } });
   emit({ mips::MipsOp::MUL, { { MipsSymbol::makeReg(mips::REG_T9), MipsSymbol::makeReg(mips::REG_A1), MipsSymbol::makeReg(mips::REG_T8) } } });
   emit({ mips::MipsOp::ADD, { { MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeReg(mips::REG_T9) } } });
   emit({ mips::MipsOp::LW, { { MipsSymbol::makeReg(mips::REG_V0), MipsSymbol::makeAddressReg(mips::REG_A0) } } });
   emit({ mips::MipsOp::JR, { { MipsSymbol::makeReg(mips::REG_RA) } } });
}

void Ir2Mips::injectInitIntArray ()
{
    /*
    initIntArray:
	# $a0=address of array, $a1 = size of array, $a2 = value
	li $s0, 0
	startloop:
	beq $s0, $a1, endloop
	sw $a2, ($a0)
	addi $a0, $a0, 4
	addi $s0, $s0, 1
	j startloop
	endloop: jr $ra
    */
   
   auto startLabel = MipsSymbol::makeLabel("initIntArrayStartLoop");
   auto endLabel = MipsSymbol::makeLabel("initIntArrayEndLoop");
   mips_.newFunction("initIntArray");
   emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeConst(0) } } });
   emit({ mips::MipsOp::INST_LABEL, { { startLabel} } });
   emit({ mips::MipsOp::BEQ, { { MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeReg(mips::REG_A1), endLabel } } });
   emit({ mips::MipsOp::SW, { { MipsSymbol::makeReg(mips::REG_A2), MipsSymbol::makeAddressReg(mips::REG_A0) } } });
   emit({ mips::MipsOp::ADDI, { { MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeReg(mips::REG_A0), MipsSymbol::makeConst(4) } } });
   emit({ mips::MipsOp::ADDI, { { MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeReg(mips::REG_T8), MipsSymbol::makeConst(1) } } });
   emit({ mips::MipsOp::J, { { startLabel } } });
   emit({ mips::MipsOp::INST_LABEL, { { endLabel } } });
   emit({ mips::MipsOp::JR, { { MipsSymbol::makeReg(mips::REG_RA) } } });
}

void Ir2Mips::injectProgramStart()
{
    /*
    __main__:
    jal main
    j exit
    */

   mips_.newFunction("__main__");
   emit({ mips::MipsOp::JAL, { { MipsSymbol::makeLabel("main") } } });
   emit({ mips::J, { { MipsSymbol::makeLabel("exit") } } });
}

void Ir2Mips::injectExitFunction ()
{
    /*
    exit:
	li	$v0, 10
	syscall
    */
    
    mips_.newFunction("exit");
    emit({ mips::MipsOp::LI, { { MipsSymbol::makeReg(mips::REG_V0), MipsSymbol::makeConst(10) } } });
    emit({ mips::MipsOp::SYSCALL });
}

bool Ir2Mips::isMainOrBuiltinFunction ()
{
    return curIrFunction().name() == "main";
}

void Ir2Mips::backupPersistentRegs ()
{
    curMipsFunction().addCodeComment("backup persistent registers");
    for (int i = 0; i < mips::NUM_PERSISTENT_REGS; i++)
    {
        auto reg = mips::PERSISTENT_REGS[i];
        auto tempName = curMipsFunction().name() + "_s" + std::to_string(i) + "_temp";
        auto temp = MipsSymbol::makeVar(tempName);
        curMipsFunction().addVar(temp, "0");
        emitStore(MipsSymbol::makeReg(reg), temp);
    }
}

void Ir2Mips::restorePersistentRegs ()
{
    curMipsFunction().addCodeComment("restore persistent registers");
    for (int i = 0; i < mips::NUM_PERSISTENT_REGS; i++)
    {
        auto reg = mips::PERSISTENT_REGS[i];
        auto tempName = curMipsFunction().name() + "_s" + std::to_string(i) + "_temp";
        auto temp = curMipsFunction().vars().at(tempName);
        emitLoad(temp, MipsSymbol::makeReg(reg));
    }
}
