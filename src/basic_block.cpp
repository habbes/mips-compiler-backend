#include "basic_block.h"
#include <sstream>

std::string BasicBlock::toString () const
{
    std::stringstream buf;
    buf << "Block(" << id << ",first:" << first << ",last:" << last << ")";
    return buf.str();
}

bool BasicBlock::operator== (const BasicBlock & other) const
{
    return id == other.id && first == other.first && last == other.last;
}

bool BasicBlock::contains (int i) const
{
    return i >= first && i <= last;
}