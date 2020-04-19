#include "briggs_function_reg_allocator.h"

BriggsFunctionRegAllocator::BriggsFunctionRegAllocator (const IrFunction & irFunc):
    cfg_(Cfg(irFunc)), ir_(irFunc), 
    inSets_(irFunc.numInstructions()), outSets_(irFunc.numInstructions()),
    useSets_(irFunc.numInstructions()), defs_(irFunc.numInstructions()),
    blockOutSets_(cfg_.blocks().size())
{
    livenessAnalysis();
    computeBlockLiveRanges();
    computeWebs();

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
    for (auto & item : blockLiveRanges_)
    {
        printf("var %s:\n\t", item.first.c_str());
        for (auto & range: item.second)
        {
            printf("B%d %d - %d def:%d, ", range.block, range.start, range.end, range.definesVar);
        }
        puts("");
    }
    printf("\nWEBS RANGES FOR %s\n", irFunc.name().c_str());
    for (auto & item : liveRanges_)
    {
        printf("var %s:\n\t", item.var.c_str());
        for (auto & range: item.localRanges)
        {
            printf("B%d %d - %d, ", range.block, range.start, range.end);
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

void BriggsFunctionRegAllocator::computeBlockLiveRanges ()
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
                    varLiveRanges.push_back({ .block = block.id, .start = i, .end = i, .definesVar = true });
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
                    varLiveRanges.push_back({ .block = block.id, .start = i, .end = i });
                } 
            }
        }
    }
}

BlockLiveRanges & BriggsFunctionRegAllocator::getLiveRanges (const std::string & var)
{
    if (blockLiveRanges_.count(var) == 0)
    {
        // init empty live ranges
        blockLiveRanges_.insert_or_assign(var, std::vector<BlockLiveRange>());
    }
    return blockLiveRanges_.at(var);
}

void BriggsFunctionRegAllocator::computeWebs ()
{
    std::vector<Web> webs;
    std::unordered_set<int> deleted;

    for (auto & item : blockLiveRanges_)
    {
        const auto & var = item.first;
        const auto & ranges = item.second;

        // keeps track of which web a range belongs to
        std::unordered_map<BlockLiveRange, int, LiveRangeHash> webMap;
        
        for (auto & r1 : ranges)
        {
            auto & b1 = cfg_.block(r1.block);
            for (auto & r2 : ranges)
            {
                auto & b2 = cfg_.block(r2.block);
                if (r1 == r2) continue;

                // these are not directly connected if they both define the variable
                // but they may be connected through a live range that uses both
                // in that case, they might be added to the web later
                if (r1.definesVar && r2.definesVar) continue;

                // because all blocks of interests are visited,
                // and intersecting webs are merged
                // we only need to compare direct successors
                if (!cfg_.hasSuccessor(b1, b2)) continue;

                // if block B1 is a successor of B2
                // and range R1 ends at the end of B1
                // and R2 starts at the beginning of B2 and it's non defining
                // then R2 must be using the same value as R1 and they should
                // be in the same web
                // TODO: what if R2 both defines and uses the var in the first instruction?
                if (r1.end == b1.last && r2.start == b2.first && !r2.definesVar)
                {
                    int web1 = webMap.count(r1) > 0 ? webMap[r1] : -1;
                    int web2 = webMap.count(r2) > 0 ? webMap[r2] : -1;
                    // if only r2 has been assigned a web, then add r1 to that web
                    if (web1 == -1 && web2 != -1)
                    {
                        webs[web2].localRanges.insert(r1);
                        webMap[r1] = web2;
                    }
                    // if only r1 has a web, then add r2 to that web
                    else if (web1 != -1 && web2 == -1)
                    {
                        webs[web1].localRanges.insert(r2);
                        webMap[r2] = web1;
                    }
                    // if both are in different webs, then merge the webs
                    else if (web1 != -1 && web2 != -1)
                    {
                        deleted.insert(web2);
                        for (auto r2Neighbor : webs[web2].localRanges)
                        {
                            webs[web1].localRanges.insert(r2Neighbor);
                            webMap[r2Neighbor] = web1;
                        }
                    }
                    // if none is in a web, then create a new web and move both in it
                    else if (web1 == -1 && web2 == -1)
                    {
                        webs.push_back({ var });
                        webMap[r1] = webs.size() - 1;
                        webMap[r2] = webs.size() - 1;
                    }
                    // if both are in the same web, do nothing
                }
            }
        }
    }

    // move non-deleted webs
    for (auto i = 0u; i < webs.size(); i++)
    {
        printf("copying web %s r %d\n", webs[i].var.c_str(), webs[i].localRanges.size());
        if (deleted.count(i) == 0)
        {
            liveRanges_.push_back(webs[i]);
        }
    }
}