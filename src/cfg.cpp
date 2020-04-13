#include "cfg.h"
#include <unordered_set>

Cfg::Cfg (const IrFunction & function): function_(function)
{
    buildCfg();
}

void Cfg::buildCfg ()
{
    // find leader statements
    auto leaders = findLeaders();
    findBasicBlocks(leaders);
}

void Cfg::findBasicBlocks (const std::vector<int> & leaders)
{
    for (int i = 0; i < leaders.size(); i++)
    {
        BasicBlock block = { .id = i, .first = leaders[i] };
        if (i + 1 < leaders.size())
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

        if (inst.op == OpCode::LABEL)
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

const CfgBlocksList & Cfg::blocks () const
{
    return blocks_;
}
