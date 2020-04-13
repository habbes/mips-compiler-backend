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
    for (int i = 0; i < ir_.numFunctions(); i++)
    {
        funcIndex_ = 0;
        translateNextFunction();
    }
    return mips_;
}

void Ir2Mips::translateNextFunction()
{
    auto & irFunc = ir_[funcIndex_];
    mips_.newFunction(irFunc);
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
        MipsInstruction inst = { mips::MipsOp::LI, { dest, src } };
        emit({ mips::MipsOp::LI, { dest, src } });
    }
    else
    {
        MipsInstruction inst = { mips::MipsOp::LW, { dest, src } };
        emit({ mips::MipsOp::LW, { dest, src } });
    }
    
}

void Ir2Mips::translateNextInstruction()
{
    auto & inst = nextIrInstruction();
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
            translateBinary(inst);
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
        inst.op == OpCode::MULT ? mips::MUL : mips::INVALID;
    emit({ op, { mipsLeft, mipsRight, mipsLeft } });
    emit({ mips::MipsOp::SW, { mipsLeft, mipsDest }});
}

void Ir2Mips::translateReturn (const IrInstruction &inst)
{
    emit({ mips::MipsOp::JR, { MipsSymbol::makeReg(mips::REG_RA) } });
}