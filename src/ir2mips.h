#pragma once

#include "ir_program.h"
#include "mips_program.h"

class Ir2Mips
{
    IrProgram &ir_;
    mips::MipsProgram mips_;
    int instIndex_;
    int funcIndex_;

    const IrInstruction &nextIrInstruction();
    const IrFunction &curIrFunction();
    mips::MipsFunction &curMipsFunction();
    void addMipsInstruction(mips::MipsInstruction);
    void translateNextFunction();
    void translateNextInstruction();
    void translateAssign(const IrInstruction &);
public:
    Ir2Mips(IrProgram & ir);
    mips::MipsProgram &translate();
    const mips::MipsProgram &mips() const;
};
