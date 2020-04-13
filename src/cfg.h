#pragma once

#include <vector>
#include <unordered_map>
#include "ir_function.h"
#include "basic_block.h"

typedef std::vector<BasicBlock> CfgBlocksList;

struct CfgNode
{
    int block;
    std::vector<int> successors;
    std::vector<int> predecessors;
};

class Cfg
{
    CfgBlocksList blocks_;
    std::unordered_map<int, int> statementToBlockMap_;
    std::vector<CfgNode> nodes_;
    const IrFunction & function_;

    void buildCfg();
    void findBasicBlocks(const std::vector<int> & leaders);
    std::vector<int> findLeaders();
public:
    Cfg(const IrFunction & function_);
    const BasicBlock &block(int i) const;
    const CfgBlocksList &blocks() const;
};