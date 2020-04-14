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
typedef std::unordered_map<std::string, std::string> MipsInitVals;

class MipsFunction
{
    std::string name_;
    MipsInstructionList instructions_;
    MipsVarMap vars_;
    MipsInitVals initialValues_;
    bool backupRa_ = false;
    std::string raBackupVarName_;

public:
    MipsFunction(const std::string & name);
    MipsFunction(const IrFunction & ir);
    void addVar(const MipsSymbol & var, const std::string & initVal);
    void addInstruction(MipsInstruction instruction);
    const MipsInstruction &instruction(int i) const;
    int numInstructions() const;
    std::string name() const;
    const MipsVarMap &vars() const;
    const MipsInitVals &initialValues() const;
    // whether to backup $ra in order to restore it after a call
    bool backsUpRa () const;
    // name of variable used to backup return address
    std::string backupRaVarName () const;
    const MipsSymbol & backupRaVar () const;
};

}