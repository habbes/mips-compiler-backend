#pragma once

#include <unordered_set>

struct CfgNode
{
    int block;
    std::unordered_set<int> successors;
    std::unordered_set<int> predecessors;

    bool operator==(const CfgNode & other) const;
    std::string toString() const;
};
