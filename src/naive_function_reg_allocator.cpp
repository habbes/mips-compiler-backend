#include "naive_function_reg_allocator.h"
#include "mips_reg.h"

using mips::MipsSymbol;

void NaiveFunctionRegAllocator::afterInstruction (Ir2Mips & compiler, int irInstIndex)
{
    auto & inst = compiler.curIrFunction().instruction(irInstIndex);
    if (inst.isAssign() || inst.isArithmeticLogic())
    {
        // result is stored in t8 by the naive convention
        // so we store that back to the dest variable
        compiler.emitStore(MipsSymbol::makeReg(mips::REG_T8),
            compiler.curMipsFunction().vars().at(inst.returnValue().name));
        // mipsFunc.addInstruction({ mips::MipsOp::SW,
        //     { MipsSymbol::makeReg(mips::REG_T8), mipsFunc.vars().at(inst.returnValue().name) } });
    }
}