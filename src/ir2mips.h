#pragma once

#include "ir_program.h"
#include "mips_program.h"
#include "base_reg_allocator.h"

class Ir2Mips
{
    IrProgram &ir_;
    mips::MipsProgram mips_;
    int instIndex_;
    int funcIndex_;
    BaseRegAllocator & regAllocator_;
    FunctionRegAllocatorPtr curFuncRegAllocator_ = nullptr;

    const IrInstruction &nextIrInstruction();
    void translateNextFunction();
    void translateNextInstruction();
    void translateAssign(const IrInstruction &);
    void translateLabel(const IrInstruction &);
    void translateBinary(const IrInstruction &);
    void translateGoto(const IrInstruction &);
    void translateConditionalBranch(const IrInstruction &);
    void translateCall(const IrInstruction &);
    void translateArrayLoad(const IrInstruction &);
    void translateArrayStore(const IrInstruction &);
    void translateReturn(const IrInstruction &);
    void injectBuiltInFunctions();
    void injectProgramStart();
    void injectPrintiFunction();
    void injectLoadIntArray();
    void injectStoreIntArray();
    void injectInitIntArray();
    void injectExitFunction();
    bool isMainOrBuiltinFunction();
    void backupPersistentRegs();
    void restorePersistentRegs();
public:
    Ir2Mips(IrProgram & ir, BaseRegAllocator &);
    mips::MipsProgram &translate();
    const mips::MipsProgram &mips() const;
    const IrFunction &curIrFunction();
    mips::MipsFunction &curMipsFunction();
    /**
     * converts the IR symbol to a corresponding MIPS symbol
     * isDef is true when the symbol is being defined/assigned a value
     * and false when its value is being used
     */
    mips::MipsSymbol irToMipsSymbol(const SymbolInfo &, bool isDef = false);
    void emit(mips::MipsInstruction);
    // loads/moves data from src to dest register
    void emitLoad(const mips::MipsSymbol & src, const mips::MipsSymbol & dest);
    // stores/moves data from src register to dest
    void emitStore(const mips::MipsSymbol & src, const mips::MipsSymbol & dest);
};
