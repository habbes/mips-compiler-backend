#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "symbol.h"
#include "ir_instruction.h"

typedef std::vector<SymbolInfo> ParamList;
typedef std::unordered_map<std::string, SymbolInfo> VarMap;

class IrFunction
{
    std::string name_;
    SymbolInfo returnType_;
    std::vector<SymbolInfo> params_;
    std::unordered_map<std::string, SymbolInfo> vars_;
    std::vector<std::unique_ptr<IrInstruction>> instructions_;
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
};