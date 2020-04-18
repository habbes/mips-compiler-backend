#include "briggs_function_reg_allocator.h"

BriggsFunctionRegAllocator::BriggsFunctionRegAllocator (const IrFunction & irFunc):
    cfg_(Cfg(irFunc)), ir_(irFunc), 
    inSets_(irFunc.numInstructions()), outSets_(irFunc.numInstructions()),
    blockOutSets_(cfg_.blocks().size())
{
    livenessAnalysis();
}

void BriggsFunctionRegAllocator::livenessAnalysis ()
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto & block: cfg_.blocks())
        {
            for (int i = block.first; i <= block.last; i++)
            {
                changed = updateInstructionLiveness(i, block);
            }
        }
        
        for (auto & block: cfg_.blocks())
        {
            changed = updateBlockLiveness(block);
        }
        
    }
}

bool BriggsFunctionRegAllocator::updateInstructionLiveness (int i, const BasicBlock & block)
{
    auto & inst = ir_.instruction(i);
    auto origInSize = inSets_[i].size();
    auto origOutSize = outSets_[i].size();

    // out[i] = in[i + 1] (last instruction of block is handled separately)
    if (i != block.last)
    {
        outSets_[i].insert(inSets_[i + 1].begin(), inSets_[i + 1].end());
    }

    // in[i] = (out[i] - def[i]) union use[i]
    inSets_[i].insert(outSets_[i].begin(), outSets_[i].end());
    if (inst.hasReturnValue())
    {
        inSets_[i].erase(inst.returnValue().name);
    }

    for (auto it = inst.inputsBegin(); it != inst.inputsEnd(); it++)
    {
        inSets_[i].insert(it->name);
    }

    return inSets_[i].size() != origInSize && outSets_[i].size() != origOutSize;
}

bool BriggsFunctionRegAllocator::updateBlockLiveness (const BasicBlock & block)
{
    auto origOutSize = blockOutSets_[block.id].size();

    // out[B] = union for B' in successors(B) (in[B'])
    for (auto & successor: cfg_.successors(block))
    {
        auto & successorIn = inSets_[successor.first];
        blockOutSets_[block.id].insert(successorIn.begin(), successorIn.end());
    }

    if (origOutSize == blockOutSets_[block.id].size())
    {
        // nothing to update
        return false;
    }

    outSets_[block.last].insert(blockOutSets_[block.id].begin(), blockOutSets_[block.id].end());

    return true;
}
