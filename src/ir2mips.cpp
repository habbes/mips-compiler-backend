#include "ir2mips.h"
#include "mips_reg.h"
#include <string>

using mips::MipsInstruction;
using mips::MipsSymbol;

Ir2Mips::Ir2Mips (IrProgram & ir): ir_(ir), instIndex_(0), funcIndex_(0)
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
        funcIndex_ = 0;
        translateNextFunction();
    }

    injectBuiltInFunctions();

    return mips_;
}

void Ir2Mips::translateNextFunction()
{
    auto & irFunc = ir_[funcIndex_];
    mips_.newFunction(irFunc);

    if (curMipsFunction().backsUpRa())
    {
        // backup $ra
        // sw $ra, func_saved_ra
        emit({ mips::MipsOp::SW, { MipsSymbol::makeReg(mips::REG_RA), curMipsFunction().backupRaVar() } });
    }

    instIndex_ = 0;
    while (instIndex_ < irFunc.numInstructions())
    {
        translateNextInstruction();
    }
}

const IrInstruction &Ir2Mips::nextIrInstruction()
{
    auto & irFunc = ir_[funcIndex_];
    auto & inst = irFunc.instruction(instIndex_);
    instIndex_++;
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

MipsSymbol Ir2Mips::irToMipsSymbol (const SymbolInfo &irSym)
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
    return curMipsFunction().vars().at(irSym.name);
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
    else
    {
        emit({ mips::MipsOp::LW, { dest, src } });
    }
}

void Ir2Mips::translateNextInstruction()
{
    auto & inst = nextIrInstruction();
    curMipsFunction().addCodeComment(inst.toString());

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
        case OpCode::RETURN:
            translateReturn(inst);
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
    auto & irDest = inst.params[0];
    auto & irSrc = inst.params[1];
    auto & mipsDest = curMipsFunction().vars().at(irDest.name);
    MipsSymbol mipsSrc = MipsSymbol::makeReg(mips::REG_T8);
    emitLoad(irToMipsSymbol(irSrc), mipsSrc);
    emit({ mips::MipsOp::SW, { mipsSrc, mipsDest } });
}

void Ir2Mips::translateBinary(const IrInstruction &inst)
{
    auto & irLeft = inst.params[0];
    auto & irRight = inst.params[1];
    auto & irDest = inst.params[2];
    auto mipsLeft = MipsSymbol::makeReg(mips::REG_T8);
    auto mipsRight = MipsSymbol::makeReg(mips::REG_T9);
    auto mipsDest = irToMipsSymbol(irDest);

    emitLoad(irToMipsSymbol(irLeft), mipsLeft);
    emitLoad(irToMipsSymbol(irRight), mipsRight);
    mips::MipsOp op =
        inst.op == OpCode::ADD ? mips::ADD :
        inst.op == OpCode::SUB ? mips::SUB :
        inst.op == OpCode::MULT ? mips::MUL :
        inst.op == OpCode::DIV ? mips::DIV :
        inst.op == OpCode::AND ? mips::AND :
        inst.op == OpCode::OR ? mips::OR :
        mips::INVALID;
    emit({ op, { mipsLeft, mipsRight, mipsLeft } });
    emit({ mips::MipsOp::SW, { mipsLeft, mipsDest }});
}

void Ir2Mips::translateConditionalBranch(const IrInstruction &inst)
{
    auto & irLeft = inst.params[0];
    auto & irRight = inst.params[1];
    auto & irLabel = inst.params[2];
    auto mipsLeft = MipsSymbol::makeReg(mips::REG_T8);
    auto mipsRight = MipsSymbol::makeReg(mips::REG_T9);
    auto mipsLabel = irToMipsSymbol(irLabel);

    emitLoad(irToMipsSymbol(irLeft), mipsLeft);
    emitLoad(irToMipsSymbol(irRight), mipsRight);
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
        it += i;
        emitLoad(irToMipsSymbol(*it), MipsSymbol::makeReg(regs[i]));
    }

    emit({ mips::MipsOp::JAL, { MipsSymbol::makeLabel(inst.label().name) } });

    if (inst.hasReturnValue())
    {
        // store return from $v0
        emit({ mips::MipsOp::SW, { MipsSymbol::makeReg(mips::REG_V0), irToMipsSymbol(inst.returnValue()) } });
    }
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

    emit({ mips::MipsOp::JR, { MipsSymbol::makeReg(mips::REG_RA) } });
}

void Ir2Mips::injectBuiltInFunctions ()
{
    injectPrintiFunction();
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
