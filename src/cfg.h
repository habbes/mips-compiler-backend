#pragma once

#include <vector>
#include <unordered_map>
#include "ir_function.h"
#include "basic_block.h"
#include "cfg_node.h"

typedef std::vector<BasicBlock> CfgBlockList;
typedef std::vector<CfgNode> CfgNodeList;

class Cfg
{
    CfgBlockList blocks_;
    std::unordered_map<int, int> statementToBlockMap_;
    std::vector<CfgNode> nodes_;
    const IrFunction & function_;

    void buildCfg();
    void findBasicBlocks(const std::vector<int> & leaders);
    void connectBasicBlocks();
    std::vector<int> findLeaders();
public:
    Cfg(const IrFunction & function_);
    const BasicBlock &block(int i) const;
    const CfgBlockList &blocks() const;
    const CfgNodeList &nodes() const;
};