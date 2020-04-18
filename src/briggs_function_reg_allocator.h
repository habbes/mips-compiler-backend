#pragma once

#include <vector>
#include <unordered_set>
#include "cfg.h"
#include "base_function_reg_allocator.h"

typedef std::unordered_set<std::string> VarSet;

class BriggsFunctionRegAllocator: public BaseFunctionRegAllocator
{
    Cfg cfg_;
    const IrFunction & ir_;
    // variables that are live at each instruction
    std::vector<VarSet> inSets_;
    // variables that are live after instruction
    std::vector<VarSet> outSets_;
    // outset of each block
    std::vector<VarSet> blockOutSets_;

    bool updateInstructionLiveness(int index, const BasicBlock & block);
    bool updateBlockLiveness(const BasicBlock & block);
    void livenessAnalysis();

public:
    BriggsFunctionRegAllocator(const IrFunction &);
};