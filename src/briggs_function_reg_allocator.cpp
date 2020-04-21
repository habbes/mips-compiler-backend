#include "briggs_function_reg_allocator.h"
#include "mips_reg.h"
#include <iostream>

BriggsFunctionRegAllocator::BriggsFunctionRegAllocator (const IrFunction & irFunc):
    cfg_(Cfg(irFunc)), ir_(irFunc),
    ig_(mips::NUM_PERSISTENT_REGS),
    inSets_(irFunc.numInstructions()), outSets_(irFunc.numInstructions()),
    useSets_(irFunc.numInstructions()), defs_(irFunc.numInstructions()),
    blockOutSets_(cfg_.blocks().size()),
    defAllocs_(irFunc.numInstructions()), useAllocs_(irFunc.numInstructions())
{
    livenessAnalysis();
    computeBlockLiveRanges();
    computeWebs();
    buildInterferenceGraph();
    ig_.colorGraph();
    allocateRegisters();
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
        defs_[i] = inst.hasReturnValue() && !inst.isReturn() ? inst.returnValue().name : "";
        
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

    // out[i] = in[i + 1]
    // last instruction of block is handled separately
    if (i != block.last)
    {
        outSets_[i].insert(inSets_[i + 1].begin(), inSets_[i + 1].end());
    }

    // in[i] = (out[i] - def[i]) union use[i]
    inSets_[i].insert(outSets_[i].begin(), outSets_[i].end());
    inSets_[i].erase(defs_[i]);
    inSets_[i].insert(useSets_[i].begin(), useSets_[i].end());

    return inSets_[i].size() != origInSize || outSets_[i].size() != origOutSize;
}

bool BriggsFunctionRegAllocator::updateBlockLiveness (const BasicBlock & block)
{
    auto origOutSize = blockOutSets_[block.id].size();

    // out[B] = union of in[B'] for B' in successors(B)
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

    // update live sets of last instruction
    outSets_[block.last].insert(blockOutSets_[block.id].begin(), blockOutSets_[block.id].end());
    inSets_[block.last].insert(outSets_[block.last].begin(), outSets_[block.last].end());
    inSets_[block.last].erase(defs_[block.last]);
    inSets_[block.last].insert(useSets_[block.last].begin(), useSets_[block.last].end());
 
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
                
                auto & varLiveRanges = getLiveRanges(var);
                if (!varLiveRanges.empty() && inSets_[i].count(var) > 0)
                {
                    // if the var is both used and assigned at this instruction,
                    // e.g. var = var + 1
                    // then extend the life of the use value before
                    // starting a new live range
                    varLiveRanges.back().end = i; //inSets_[i].count(var) > 0 ? i : i - 1;
                }
                // start a new live range if this var is used later
                if (outSets_[i].count(var) > 0)
                {
                    varLiveRanges.push_back({ .block = block.id, .start = i, .end = i, .definesVar = true });
                }
            }

            // for each variable that's live at this instruction, extend live range
            for (auto & var : inSets_[i])
            {
                // don't extend the life of the killed variable
                if (defs_[i] == var) continue;

                auto & varLiveRanges = getLiveRanges(var);
                if (!varLiveRanges.empty() && block.contains(varLiveRanges.back().end))
                {
                    // extend current range in this block
                    varLiveRanges.back().end = i;
                }
                else
                {
                    // start a new live range in this block
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

            // if not already in a web, put r1 in its own web
            if (webMap.count(r1) == 0)
            {
                webs.push_back({ var, .localRanges = { r1 } });
                webMap[r1] = webs.size() - 1;
            }

            for (auto & r2 : ranges)
            {
                auto & b2 = cfg_.block(r2.block);
                if (r1 == r2) continue;

                // these are not directly connected if they both define the variable
                // but they may be connected through a live range that uses both
                // in that case, their webs will be merged later
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
                    else if (web1 != -1 && web2 != -1 && web1 != web2)
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
                        webs.push_back({ var, .localRanges = { r1, r2 } });
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
        if (deleted.count(i) == 0)
        {
            liveRanges_.push_back(webs[i]);
        }
    }
}

void BriggsFunctionRegAllocator::buildInterferenceGraph ()
{
    for (auto & web : liveRanges_)
    {
        ig_.addNode(web.id(), estimateSpillCost(web));
    }

    for (auto web = liveRanges_.begin(); web != liveRanges_.end(); web++)
    {
        for (auto otherWeb = web + 1; otherWeb != liveRanges_.end(); otherWeb++)
        {
            if (web->interferesWith(*otherWeb))
            {
                ig_.connectNodes(web->id(), otherWeb->id());
            }
        }
    }
}

int BriggsFunctionRegAllocator::estimateSpillCost(const Web & web) const
{
    int cost = 0;
    for (auto & range : web.localRanges)
    {
        int rangeCost = 0;
        int blockWeight = 1;
        // check if it's a loop
        // quick hack: if it ends with a loop_label_... branch, then assume it's a loop
        // not that robust, but good enough for now. Also doesn't account for nested loops
        auto lastInstIndex = cfg_.block(range.block).last;
        auto & lastInst = ir_.instruction(lastInstIndex);
        if (lastInst.isBranch() && lastInst.label().name.find("loop_label") != std::string::npos)
        {
            // if it's a loop, assume it runs on average 10 times
            blockWeight = 10;
        }

        for (int i = range.start; i <= range.end; i++)
        {
            // the same instruction can have both a use and a def in
            // two consecutive ranges,
            // use range.definesVar to distinguish between
            // the range with the use, and range with the definition
            if (defs_[i] == web.var && range.definesVar)
            {
                // assume store cost = 1
                rangeCost++;
            }
            else if (useSets_[i].count(web.var) != 0)
            {
                // assume load cost = 1
                rangeCost++;
            }
        }
        
        cost += rangeCost * blockWeight;
    }

    return cost;
}

void BriggsFunctionRegAllocator::allocateRegisters ()
{
    for (auto & web : liveRanges_)
    {
        auto & node = ig_.node(web.id());

        // this web will spill
        if (!node.hasColor()) continue;

        // register to allocate to this variable in this live range web
        auto reg = mips::PERSISTENT_REGS[node.color];
        
        for (auto & range : web.localRanges)
        {
            // for each instruction in this range
            // map this variable to the assigned register
            for (int i = range.start; i <= range.end; i++)
            {
                if (defs_[i] == web.var && range.definesVar)
                {
                    defAllocs_[i] = reg;
                }
                else if (inSets_[i].count(web.var) != 0)
                {
                    useAllocs_[i].insert_or_assign(web.var, reg);
                }
            }
        }
    }
}

MipsSymbol BriggsFunctionRegAllocator::getRegIfAllocated (const MipsSymbol & var, int irInstIndex, bool isDef)
{
    if (irInstIndex < 0)
    {
        // queries made before the first instruction are for function arguments
        if (defs_[0] == var.name && !defAllocs_[0].empty())
        {
            return MipsSymbol::makeReg(defAllocs_[0]);
        }
        auto item = useAllocs_[0].find(var.name);
        if (item != useAllocs_[0].end())
        {
            return MipsSymbol::makeReg(item->second);
        }

        return  var;
    }

    // check if var is being assigned
    if (isDef && defs_[irInstIndex] == var.name && !defAllocs_[irInstIndex].empty())
    {
        return MipsSymbol::makeReg(defAllocs_[irInstIndex]);
    }

    // var is being used
    auto item = useAllocs_[irInstIndex].find(var.name);
    if (item != useAllocs_[irInstIndex].end())
    {
        return MipsSymbol::makeReg(item->second);
    }
    
    // no register allocated for this var
    return var;
}