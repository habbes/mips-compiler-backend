#pragma once

#include <vector>
#include <unordered_set>
#include "cfg.h"
#include "base_function_reg_allocator.h"

struct LiveRange
{
    int start;
    int end;
};

typedef std::vector<LiveRange> LiveRanges;
typedef std::unordered_map<std::string, LiveRanges> VarLiveRanges;
typedef std::unordered_set<std::string> VarSet;

class BriggsFunctionRegAllocator: public BaseFunctionRegAllocator
{
    Cfg cfg_;
    const IrFunction & ir_;
    // variables that are live at each instruction
    std::vector<VarSet> inSets_;
    // variables that are live after instruction
    std::vector<VarSet> outSets_;
    // variables used as inputs in each instruction
    std::vector<VarSet> useSets_;
    // variable defined/killed at each instruction, empty otherwise
    std::vector<std::string> defs_;
    // outset of each block
    std::vector<VarSet> blockOutSets_;
    VarLiveRanges liveRanges_;
    void initUseAndDefSets();
    bool updateInstructionLiveness(int index, const BasicBlock & block);
    bool updateBlockLiveness(const BasicBlock & block);
    void livenessAnalysis();
    void computeLiveRanges();
    LiveRanges & getLiveRanges(const std::string & var);
public:
    BriggsFunctionRegAllocator(const IrFunction &);
};