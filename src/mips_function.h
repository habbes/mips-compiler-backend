#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "mips_instruction.h"
#include "ir_function.h"

namespace mips
{

typedef std::unique_ptr<MipsInstruction> MipsInstructionUPtr;
typedef std::vector<std::unique_ptr<MipsInstruction>> MipsInstructionList;
typedef std::unordered_map<std::string, MipsSymbol> MipsVarMap;

class MipsFunction
{
    std::string name_;
    MipsInstructionList instructions_;
    MipsVarMap vars_;
    std::unordered_map<std::string, std::string> initialValues_;

public:
    MipsFunction(const std::string & name);
    MipsFunction(const IrFunction & ir);
    void addVar(const MipsSymbol & var, const std::string & initVal);
    void addInstruction(MipsInstructionUPtr instruction);
};

}