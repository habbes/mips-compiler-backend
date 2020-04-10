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

void Ir2Mips::addMipsInstruction (mips::MipsInstruction inst)
{
    curMipsFunction().addInstruction(std::move(inst));
}

void Ir2Mips::translateNextInstruction()
{
    auto & inst = nextIrInstruction();
    switch (inst.op)
    {
        case OpCode::ASSIGN:
            translateAssign(inst);
            break;
    }
}

void Ir2Mips::translateAssign(const IrInstruction &inst)
{
    /*
    IR:     assign, dest, 10
    MIPS:   li $t0, 10
            sw $t0, dest
    
    IR:     assign, dest, src
    MIPS:   lw $t0, src
            sw $t0, dest
    */
    auto & irDest = inst.params[0];
    auto & irSrc = inst.params[1];
    auto & mipsDest = curMipsFunction().vars().at(irDest.name);
    MipsSymbol mipsSrc;
    if (irSrc.type == SymbolType::CONST)
    {

        // li $t0, 10
        mipsSrc = MipsSymbol::makeReg(mips::REG_T8);
        MipsInstruction loadInst = {
            mips::MipsOp::LI,
            {
                mipsSrc,
                MipsSymbol::makeConst(irSrc.intValue)
            }
        };
        addMipsInstruction(loadInst);
    }
    else
    {
        // lw $t0, src
        mipsSrc = MipsSymbol::makeReg(mips::REG_T8);
        MipsInstruction loadInst = {
            mips::MipsOp::LW,
            {
                mipsSrc,
                curMipsFunction().vars().at(irSrc.name)
            }
        };
        addMipsInstruction(loadInst);
    }
    
    addMipsInstruction({ mips::MipsOp::SW, { mipsSrc, mipsDest } });
}