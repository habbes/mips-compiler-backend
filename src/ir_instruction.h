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

typedef std::vector<SymbolInfo> IrSymbolList;
typedef IrSymbolList::const_iterator IrFuncArgsIterator;

struct IrInstruction
{
    OpCode op;
    IrSymbolList params;

    bool operator==(IrInstruction & other) const;
    bool operator!=(IrInstruction & other) const;

    const SymbolInfo & label() const;
    int funcArgsCount() const;
    IrFuncArgsIterator funcArgsBegin() const;
    IrFuncArgsIterator funcArgsEnd() const;
    const SymbolInfo & returnValue() const;
    bool isBranch() const;
    bool isConditionalBranch() const;
    bool isUnconditionalBranch() const;
    bool isLabel() const;
    bool isCall() const;
    bool hasReturnValue() const;
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