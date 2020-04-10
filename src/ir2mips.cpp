#include "ir2mips.h"

Ir2Mips::Ir2Mips (IrProgram & ir): ir_(ir)
{
    initMips();
}

const mips::MipsProgram &Ir2Mips::mips() const
{
    return mips_;
}

mips::MipsProgram &Ir2Mips::translate()
{
    return mips_;
}

void Ir2Mips::initMips ()
{
    for (int i = 0; i < ir_.numFunctions(); i++)
    {
        mips_.newFunction(ir_[i]);
    }
}