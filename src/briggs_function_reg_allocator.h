#pragma once

#include <vector>
#include <unordered_set>
#include <functional>
#include <sstream>
#include "cfg.h"
#include "base_function_reg_allocator.h"

// a local live range within a block
struct BlockLiveRange
{
    int block;
    int start;
    int end;
    // whether this live range starts with a definition
    bool definesVar = false;
    bool operator== (const BlockLiveRange & other) const
    {
        return block == other.block && start == other.start && end == other.end
            && definesVar == other.definesVar;
    }
    
    bool operator!= (const BlockLiveRange & other) const
    {
        return !(*this == other);
    }

    std::string toString () const
    {
        return std::string("B") + std::to_string(block) + " "
            + std::to_string(start) + " - " + std::to_string(end)
            + " def:" + std::to_string(definesVar);
    }
};

struct LiveRangeHash
{
  std::size_t operator()(const BlockLiveRange& k) const
  {
    using std::size_t;
    using std::hash;

    return ((hash<int>()(k.block)
             ^ (hash<int>()(k.start) << 1)) >> 1)
             ^ (hash<int>()(k.end) << 1);
  }
};

typedef std::unordered_set<BlockLiveRange, LiveRangeHash> BlockLiveRangeSet;

// a web is a "global"/inter-block live range
// it's a set that contains each def with all
// the uses it reaches, and each use and
// all the defs that reach it
struct Web
{
    std::string var;
    BlockLiveRangeSet localRanges;

    bool operator==(const Web & other) const
    {
        if (var != other.var) return false;
        if (localRanges.size() != other.localRanges.size()) return false;
        for (auto & range : localRanges)
        {
            if (other.localRanges.count(range) == 0) return false;
        }

        return true;
    }

    std::string toString() const
    {
        std::stringstream buffer;
        buffer << var << ":";
        for (auto & range: localRanges)
        {
            buffer << " " << range.toString() << ",";
        }

        return buffer.str();
    }
};

typedef std::vector<BlockLiveRange> BlockLiveRanges;
typedef std::unordered_map<std::string, BlockLiveRanges> VarBlockLiveRanges;
typedef std::unordered_set<std::string> VarSet;
typedef std::vector<Web> LiveRanges;

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
    VarBlockLiveRanges blockLiveRanges_;
    LiveRanges liveRanges_;
    void initUseAndDefSets();
    bool updateInstructionLiveness(int index, const BasicBlock & block);
    bool updateBlockLiveness(const BasicBlock & block);
    void livenessAnalysis();
    void computeBlockLiveRanges();
    void computeWebs();
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
};