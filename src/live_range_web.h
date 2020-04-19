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

    // checks whether the two ranges intersect
    // assumes that they belong to different variables
    bool interferesWith (const BlockLiveRange & other) const
    {
        if (start > other.end || other.start > end)
        {
            return false;
        }
        // if the start of one range and the end of another occur
        // at the same instruction,
        // and one is an lvalue and the other an rvalue,
        // then this does not count as interference
        // e.g. t1 = t2 + 1 (t2 and t1 can use the same register if this value of t2 is not referenced after this)
        if (start == other.end && definesVar)
        {
            return false;
        }
        if (other.start == end && other.definesVar)
        {
            return false;
        }

        return true;
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
    mutable std::string id_;

    std::string id() const
    {
        if (id_ == "")
        {
            // id is that var combined with the first insruction
            int start = localRanges.begin()->start;
            for (auto it = localRanges.begin(); it != localRanges.end(); it++)
            {
                if (it->start < start) start = it->start;
            }
            id_ = var + std::to_string(start);
        }
    
        return id_;
    }

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

    bool interferesWith (const Web & other) const
    {
        // live ranges of the same variable cannot interfer (a var can't have 2 values simultaneously)
        if (var == other.var) return false;

        for (auto & range : localRanges)
        {
            for (auto & otherRange : other.localRanges)
            {
                if (range.interferesWith(otherRange)) return true;
            }
        }

        return false;
    }
};