#include "briggs_function_reg_allocator.h"

BriggsFunctionRegAllocator::BriggsFunctionRegAllocator (const IrFunction & irFunc):
    cfg_(Cfg(irFunc)), ir_(irFunc), 
    inSets_(irFunc.numInstructions()), outSets_(irFunc.numInstructions()),
    useSets_(irFunc.numInstructions()), defs_(irFunc.numInstructions()),
    blockOutSets_(cfg_.blocks().size())
{
    livenessAnalysis();
    computeLiveRanges();

    // this is for debuggin, should replace with unit tests
    printf("LIVENESS FOR %s\n", irFunc.name().c_str());
    for (auto & block: cfg_.blocks())
    {
        printf("BLOCK %d\n", block.id);
        for (int i = block.first; i <= block.last; i++)
        {
            auto & inst = ir_.instruction(i);
            printf("%s:\t", inst.toString().c_str());
            printf("in: {");
            for (auto & var : inSets_[i])
            {
                printf("%s,", var.c_str());
            }
            printf("}\t");

            printf("out: {");
            for (auto & var : outSets_[i])
            {
                printf("%s,", var.c_str());
            }
            printf("}\t");

            printf("def: {");
            if (defs_[i] != "")
            {
                printf("%s,", defs_[i].c_str());
            }
            printf("}\t");

            printf("use: {");
            for (auto var: useSets_[i])
            {
                printf("%s,", var.c_str());
            }
            printf("}\n");
        }
    }
    printf("LIVE RANGES FOR %s\n", irFunc.name().c_str());
    for (auto & item : liveRanges_)
    {
        printf("var %s:\n\t", item.first.c_str());
        for (auto & range: item.second)
        {
            printf("%d - %d, ", range.start, range.end);
        }
        puts("");
    }
}

void BriggsFunctionRegAllocator::livenessAnalysis ()
{
    initUseAndDefSets();

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto & block: cfg_.blocks())
        {
            for (int i = block.first; i <= block.last; i++)
            {
                changed = updateInstructionLiveness(i, block) || changed;
            }
        }
        
        for (auto & block: cfg_.blocks())
        {
            changed = updateBlockLiveness(block) || changed;
        }
        
    }
}

void BriggsFunctionRegAllocator::initUseAndDefSets()
{
    for (int i = 0; i < ir_.numInstructions(); i++)
    {
        const auto & inst = ir_.instruction(i);
        defs_[i] = inst.hasReturnValue() ? inst.returnValue().name : "";
        
        for (auto input = inst.inputsBegin(); input != inst.inputsEnd(); input++)
        {
            if (input->type == SymbolType::VAR && !(input->isArray))
            {
                useSets_[i].insert(input->name);
            }
        }
    }
}

bool BriggsFunctionRegAllocator::updateInstructionLiveness (int i, const BasicBlock & block)
{
    auto origInSize = inSets_[i].size();
    auto origOutSize = outSets_[i].size();

    // out[i] = in[i + 1] (last instruction of block is handled separately)
    if (i != block.last)
    {
        outSets_[i].insert(inSets_[i + 1].begin(), inSets_[i + 1].end());
    }

    // in[i] = (out[i] - def[i]) union use[i]
    inSets_[i].insert(outSets_[i].begin(), outSets_[i].end());
    if (!defs_[i].empty())
    {
        inSets_[i].erase(defs_[i]);
    }

    inSets_[i].insert(useSets_[i].begin(), useSets_[i].end());

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

    // update outset of last instruction
    outSets_[block.last].insert(blockOutSets_[block.id].begin(), blockOutSets_[block.id].end());

    return true;
}

void BriggsFunctionRegAllocator::computeLiveRanges ()
{
    for (auto & block: cfg_.blocks())
    {
        for (int i = block.first; i <= block.last; i++)
        {
            if (defs_[i] != "")
            {
                auto var = defs_[i];
                // kill the variable, end it's range here
                auto & varLiveRanges = getLiveRanges(var);
                if (!varLiveRanges.empty())
                {
                    // if the var is used in this instruction, e.g. var = var + 1
                    // then this is the end of the range, otherwise the end
                    // is the previous instruction
                    varLiveRanges.back().end = inSets_[i].count(var) > 0 ? i : i - 1;
                }
                // start a new live range if this var is used later
                if (outSets_[i].count(var) > 0)
                {
                    varLiveRanges.push_back({ .start = i, .end = i });
                }
            }

            // for each variable that's live after this instruction, extend live range
            for (auto & var : outSets_[i])
            {
                // skip the killed variable cause it's already been processed in the block above
                if (defs_[i] == var) continue;

                auto & varLiveRanges = getLiveRanges(var);
                if (!varLiveRanges.empty())
                {
                    varLiveRanges.back().end = i;
                }
                else
                {
                    // start a new live range (this is most likely the beginning of a block)
                    varLiveRanges.push_back({ .start = i, .end = i });
                } 
            }
        }
    }
}

LiveRanges & BriggsFunctionRegAllocator::getLiveRanges (const std::string & var)
{
    if (liveRanges_.count(var) == 0)
    {
        // init empty live ranges
        liveRanges_.insert_or_assign(var, std::vector<LiveRange>());
    }
    return liveRanges_.at(var);
}