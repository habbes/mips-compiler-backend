#pragma once

#include <vector>
#include <unordered_map>
#include <ostream>
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
    CfgBlockList successors(const BasicBlock &b) const;
    CfgBlockList predecessors(const BasicBlock &b) const;
    // check whether reference has candidate as a successor
    bool hasSuccessor (const BasicBlock & reference, const BasicBlock & candidate) const;
    // prints a graphViz visualization of the graph to the specified output
    void writeViz(std::ostream & out) const;
};