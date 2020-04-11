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

std::string mips::MipsSymbol::sizeString () const
{
    switch (size)
    {
        case mips::WORD:
            return "word";
        case mips::HALF:
            return "half";
        case mips::BYTE:
            return "byte";
        case mips::FLOAT:
            return "float";
        case mips::DOUBLE:
            return "double";
        case mips::SPACE:
            return "space";
        case mips::ASCII:
            return "ascii";
        case mips::ASCIIZ:
            return "asciiz";
    }
    return "<unknown>";
}

mips::MipsSymbol mips::MipsSymbol::makeConst (int value)
{
    return { std::to_string(value), mips::MipsSymbolType::CONST };
}

mips::MipsSymbol mips::MipsSymbol::makeReg (std::string reg, mips::MipsSymbolSize dataType)
{
    return { reg, mips::MipsSymbolType::REG, dataType };
}

mips::MipsSymbol mips::MipsSymbol::makeLabel (const std::string & label)
{
    return { label, mips::LABEL };
}
