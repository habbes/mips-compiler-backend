#include "block_function_reg_allocator.h"
#include <string>
#include <algorithm>
#include "mips_reg.h"
#include "ir2mips.h"

using mips::MipsSymbol;

BlockFunctionRegAllocator::BlockFunctionRegAllocator (const IrFunction & ir):
    cfg_(Cfg(ir)), ir_(ir), instructionsAllocs_(ir.numInstructions())
{
    allocate();
}

void BlockFunctionRegAllocator::allocate()
{
    for (auto it = cfg_.blocks().begin(); it < cfg_.blocks().end(); it++)
    {
        allocateBlock(*it);
    }
}

void BlockFunctionRegAllocator::allocateBlock(const BasicBlock & block)
{
    const int numRegs = 4;
    std::string regsToAllocate[numRegs] = { mips::REG_S0, mips::REG_S1, mips::REG_S2, mips::REG_S3 };

    // count the usages of each variable in the block
    std::unordered_map<std::string, int> varUsages{};
    for (int i = block.first; i <= block.last; i++)
    {
        auto inst = ir_.instruction(i);
        if (inst.inputsCount() == 0) continue;

        for (auto input = inst.inputsBegin(); input < inst.inputsEnd(); input++)
        {
            if (input->type == SymbolType::VAR && !input->isArray)
            {
                auto usageIt = varUsages.find(input->name);
                if (usageIt == varUsages.end())
                {
                    varUsages.insert_or_assign(input->name, 0);
                }
                else
                {
                    varUsages.insert_or_assign(input->name, usageIt->second + 1);
                }
            }
        }
    }

    // sort by usage
    std::vector<std::pair<std::string, int>> sortedUsages(varUsages.begin(), varUsages.end());
    std::sort(sortedUsages.begin(), sortedUsages.end(),
        [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
            return a.second < b.second; });
    
    // allocate available registers to most-used vars
    VarToRegMap allocations;
    for (size_t i = 0; i < numRegs && i < sortedUsages.size(); i++)
    {
        auto var = sortedUsages[i].first;
        auto reg = regsToAllocate[i];
        allocations[var] = reg;
    }

    // map allocations to all instructions in this block
    for (int i = block.first; i <= block.last; i++)
    {
        instructionsAllocs_[i] = allocations;
    }

    // map loads to first instruction
    registerLoads_.insert_or_assign(block.first, allocations);
    // map restores to last instruction
    registerStores_.insert_or_assign(block.last, allocations);
}

void BlockFunctionRegAllocator::beforeInstruction (Ir2Mips & compiler, int index)
{
    // load vars into registers at the start of basic block
    auto loadsIt = registerLoads_.find(index);
    if (loadsIt == registerLoads_.end()) return;
    auto varsToLoad = loadsIt->second;
    for (auto & item: varsToLoad)
    {
        auto mipsVar = compiler.curMipsFunction().vars().at(item.first);
        auto reg = MipsSymbol::makeReg(item.second);
        compiler.emit({ mips::MipsOp::LW, { reg, mipsVar} });
    }
}

void BlockFunctionRegAllocator::afterInstruction (Ir2Mips & compiler, int index)
{
    // restore regs into vars when ending basic block
    auto it = registerStores_.find(index);
    if (it == registerStores_.end()) return;
    auto varsToRestore = it->second;
    for (auto & item: varsToRestore)
    {
        auto mipsVar = compiler.curMipsFunction().vars().at(item.first);
        auto reg = MipsSymbol::makeReg(item.second);
        compiler.emit({ mips::MipsOp::SW, { reg, mipsVar} });
    }
}