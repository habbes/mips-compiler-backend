#include "cfg_node.h"
#include <sstream>

std::string CfgNode::toString () const
{
    std::stringstream buf;
    buf << "Node(" << block << ",succ:";
    for (auto s : successors)
    {
        buf << " " << s;
    }
    buf << ",pred:";
    for (auto p: predecessors)
    {
        buf << " " << p;
    }
    buf << ")";

    return buf.str();
}

bool CfgNode::operator== (const CfgNode & other) const
{
    if (block != other.block) return false;
    if (predecessors.size() != other.predecessors.size()) return false;
    if (successors.size() != other.successors.size()) return false;

    for (auto p: predecessors)
    {
        if (other.predecessors.count(p) == 0) return false;
    }

    for (auto s: successors)
    {
        if (other.successors.count(s) == 0) return false;
    }

    return true;
}