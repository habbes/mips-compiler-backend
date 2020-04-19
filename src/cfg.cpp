#include "cfg.h"
#include <unordered_set>
#include <algorithm>

Cfg::Cfg (const IrFunction & function): function_(function)
{
    buildCfg();
}

void Cfg::buildCfg ()
{
    auto leaders = findLeaders();
    findBasicBlocks(leaders);
    connectBasicBlocks();
}

void Cfg::findBasicBlocks (const std::vector<int> & leaders)
{
    for (int i = 0; i < (int)leaders.size(); i++)
    {
        BasicBlock block = { .id = i, .first = leaders[i] };
        if (i + 1 < (int)leaders.size())
        {
            // block ends up to (but not including) next leader
            block.last = leaders[i + 1] - 1;
        }
        else
        {
            // last block goes up to end of function
            block.last = function_.numInstructions() - 1;
        }
        
        // map all instructions in this block back to this block
        for (int inst = block.first; inst <= block.last; inst++)
        {
            statementToBlockMap_.insert_or_assign(inst, block.id);
        }

        blocks_.push_back(block);
    }
}

void Cfg::connectBasicBlocks ()
{
    // nodes wrap block with metadata about which blocks are connected
    for (auto & block: blocks_)
    {
        nodes_.push_back({ .block = block.id });
    }

    // find edges between blocks
    for (auto & current: blocks_)
    {
        for (auto & other: blocks_)
        {
            if (other.id == current.id) continue;
            auto & lastOfCurrent = function_.instruction(current.last);
            auto & firstOfOther = function_.instruction(other.first);
    
            if (
                // current has a branch to other
                (lastOfCurrent.isBranch() && firstOfOther.isLabel() && lastOfCurrent.label() == firstOfOther.label())
                ||
                // current follows through to other
                (!lastOfCurrent.isUnconditionalBranch() && other.first == current.last + 1)
                )
            {
                nodes_[current.id].successors.insert(other.id);
                nodes_[other.id].predecessors.insert(current.id);
            }
        }
    }
}

std::vector<int> Cfg::findLeaders ()
{
    std::vector<int> leaders;
    std::unordered_set<std::string> targetLabels;
    std::unordered_map<std::string, int> labelStatements;

    for (int i = 0; i < function_.numInstructions(); i++)
    {
        auto & inst = function_.instruction(i);
        if (i == 0)
        {
            // first statement in function is a leader
            leaders.push_back(i);
        }
        else
        {
            // statements following a branch are leaders
            auto & prev = function_.instruction(i - 1);
            if (prev.isBranch())
            {
                leaders.push_back(i);
            }
        }
    
        if (inst.isBranch())
        {
            targetLabels.insert(inst.label().name);
        }

        if (inst.isLabel())
        {
            labelStatements.insert_or_assign(inst.label().name, i);
        }
    }

    // find leaders that correspond to branch targets
    for (auto & label : targetLabels)
    {
        auto it = labelStatements.find(label);
        auto i = (*it).second;
        auto foundIt = std::find(leaders.begin(), leaders.end(), i);
        if (foundIt == leaders.end())
        {
            leaders.push_back(i);
        }
    }

    std::sort(leaders.begin(), leaders.end());
    return leaders;
}

const BasicBlock & Cfg::block (int i) const
{
    return blocks_[i];
}

const CfgBlockList & Cfg::blocks () const
{
    return blocks_;
}

const CfgNodeList & Cfg::nodes () const
{
    return nodes_;
}

CfgBlockList Cfg::successors (const BasicBlock & block) const
{
    // TODO should probably implement a pair of iterators
    // that automatically return the block object when dereferenced
    // instead of creating a new vector each time this is called
    auto node = nodes_[block.id];
    CfgBlockList result;
    std::transform(
        node.successors.begin(), node.successors.end(), std::back_inserter(result),
        [&](int successor) { return this->block(successor); });

    return result;
}

CfgBlockList Cfg::predecessors (const BasicBlock & block) const
{
    auto node = nodes_[block.id];
    CfgBlockList result;
    std::transform(
        node.predecessors.begin(), node.predecessors.end(), std::back_inserter(result),
        [&](int successor) { return this->block(successor); });

    return result;
}

bool Cfg::hasSuccessor (const BasicBlock & reference, const BasicBlock & candidate) const
{
    return nodes_[reference.id].successors.count(candidate.id) > 0;
}
