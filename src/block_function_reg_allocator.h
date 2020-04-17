#pragma once

#include <vector>
#include <unordered_map>
#include "base_function_reg_allocator.h"
#include "cfg.h"

// variable -> register allocation map
typedef std::unordered_map<std::string, std::string> VarToRegMap;


class BlockFunctionRegAllocator: public BaseFunctionRegAllocator
{
    Cfg cfg_;
    const IrFunction & ir_;
    // mapping of variable to register for each instruction
    std::vector<VarToRegMap> instructionsAllocs_;
    // instructions before which vars should be loaded into regs
    std::unordered_map<int, VarToRegMap> registerLoads_;
    // instructions after which vars should be restored from regs
    std::unordered_map<int, VarToRegMap> registerStores_;
    
    void allocate();
    void allocateBlock(const BasicBlock &);
public:
    BlockFunctionRegAllocator(const IrFunction &);
    void beforeInstruction(Ir2Mips &, int irInstIndex) override;
    void afterInstruction(Ir2Mips &, int irInstIndex) override;
};