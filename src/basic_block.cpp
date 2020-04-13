#include "basic_block.h"
#include <sstream>

std::string BasicBlock::toString () const
{
    std::stringstream buf;
    buf << "Block(" << id << ",first:" << first << ",last:" << last << ")";
    return buf.str();
}

bool BasicBlock::operator== (const std::string & other) const
{
    return toString() == other;
}