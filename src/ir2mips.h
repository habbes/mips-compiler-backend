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
    mips::MipsSymbol irToMipsSymbol(const SymbolInfo &);
    void emitMips(mips::MipsInstruction);
    void emitLoad(const mips::MipsSymbol &, const mips::MipsSymbol &);
    void translateNextFunction();
    void translateNextInstruction();
    void translateAssign(const IrInstruction &);
    void translateLabel(const IrInstruction &);
    void translateBinary(const IrInstruction &);
    void translateReturn(const IrInstruction &);
public:
    Ir2Mips(IrProgram & ir);
    mips::MipsProgram &translate();
    const mips::MipsProgram &mips() const;
};
