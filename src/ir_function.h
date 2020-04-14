#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "symbol.h"
#include "ir_instruction.h"

typedef std::vector<SymbolInfo> ParamList;
typedef std::unordered_map<std::string, SymbolInfo> VarMap;
typedef std::vector<std::unique_ptr<IrInstruction>> InstructionList;

class IrFunction
{
    std::string name_;
    SymbolInfo returnType_;
    ParamList params_;
    VarMap vars_;
    InstructionList instructions_;
    bool makesCalls_;
public:
    IrFunction(const std::string & name);
    const std::string & name() const;
    void setName(std::string &);
    void setReturnType(SymbolInfo);
    const SymbolInfo &returnType() const;
    void addParam(SymbolInfo);
    const ParamList &params() const;
    void addVar(SymbolInfo);
    const VarMap &vars() const;
    void addInstruction(IrInstructionUPtr instruction);
    const IrInstruction & instruction(int i) const;
    int numInstructions() const;
    // whether the function calls other functions
    bool makesCalls() const;
};