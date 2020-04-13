#pragma once

#include <string>
#include <vector>
#include <memory>
#include "symbol.h"

enum OpCode
{
    ADD,
    SUB,
    MULT,
    DIV,
    AND,
    OR,
    GOTO,
    BREQ,
    BRNEQ,
    BRLT,
    BRGT,
    BRGEQ,
    BRLEQ,
    RETURN,
    CALL,
    CALLR,
    ARRAY_STORE,
    ARRAY_LOAD,
    ASSIGN,
    LABEL,
    INVALID = -1
};

struct IrInstruction
{
    OpCode op;
    std::vector<SymbolInfo> params;

    bool operator==(IrInstruction & other) const;
    bool operator!=(IrInstruction & other) const;

    const SymbolInfo & label() const;
    bool isBranch() const;
    std::string toString() const;
};

typedef std::unique_ptr<IrInstruction> IrInstructionUPtr;

class IrInstructionBuilder
{
    IrInstructionUPtr instruction_;
public:
    IrInstructionBuilder(OpCode op);
    static IrInstructionBuilder fromOp(OpCode op);
    IrInstructionBuilder &param(SymbolInfo symbol);
    IrInstructionUPtr build();
};

OpCode stringToOpCode(const std::string & codeText);