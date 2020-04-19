#pragma once

#include <vector>
#include <unordered_set>
#include <functional>
#include <sstream>
#include "cfg.h"
#include "base_function_reg_allocator.h"
#include "live_range_web.h"
#include "interference_graph.h"

typedef std::vector<BlockLiveRange> BlockLiveRanges;
typedef std::unordered_map<std::string, BlockLiveRanges> VarBlockLiveRanges;
typedef std::unordered_set<std::string> VarSet;
typedef std::vector<Web> LiveRanges;

class BriggsFunctionRegAllocator: public BaseFunctionRegAllocator
{
    Cfg cfg_;
    const IrFunction & ir_;
    InterferenceGraph ig_;
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
    VarBlockLiveRanges blockLiveRanges_;
    LiveRanges liveRanges_;

    void initUseAndDefSets();
    bool updateInstructionLiveness(int index, const BasicBlock & block);
    bool updateBlockLiveness(const BasicBlock & block);
    void livenessAnalysis();
    void computeBlockLiveRanges();
    void computeWebs();
    void buildInterferenceGraph();
    int estimateSpillCost(const Web & web) const;
    BlockLiveRanges & getLiveRanges(const std::string & var);
public:
    BriggsFunctionRegAllocator(const IrFunction &);

    const std::vector<VarSet> & inSets() const
    {
        return inSets_;
    }

    const std::vector<VarSet> & outSets() const
    {
        return outSets_;
    }

    const std::vector<VarSet> & useSets() const
    {
        return useSets_;
    }

    const std::vector<std::string> & defs() const
    {
        return defs_;
    }

    const VarBlockLiveRanges & blockLiveRanges() const
    {
        return blockLiveRanges_;
    }

    const LiveRanges & liveRanges() const
    {
        return liveRanges_;
    }

    const InterferenceGraph & interferenceGraph () const
    {
        return ig_;
    }
};