#include "mips_symbol.h"
#include <sstream>

bool mips::MipsSymbol::operator== (const MipsSymbol & other) const
{
    return type == other.type
        && size == other.size
        && name == other.name;
}

bool mips::MipsSymbol::operator!= (const MipsSymbol & other) const
{
    return !(*this == other);
}

std::string mips::MipsSymbol::toString () const
{
    std::stringstream buffer;
    buffer << "MipsSymbol(n:" << name
        << ",t:" << type
        << ",s:" << size
        << ")";
    return buffer.str();
}

mips::MipsSymbol mips::MipsSymbol::makeConst (int value)
{
    return { std::to_string(value), mips::MipsSymbolType::CONST };
}

mips::MipsSymbol mips::MipsSymbol::makeReg (std::string reg, mips::MipsSymbolSize dataType)
{
    return { reg, mips::MipsSymbolType::REG, dataType };
}