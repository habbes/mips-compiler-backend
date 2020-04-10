#pragma once

#include "ir_program.h"
#include "mips_program.h"

class Ir2Mips
{
    IrProgram &ir_;
    mips::MipsProgram mips_;
    void initMips();
public:
    Ir2Mips(IrProgram & ir);
    mips::MipsProgram &translate();
    const mips::MipsProgram &mips() const;
};
