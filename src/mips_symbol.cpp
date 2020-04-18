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

bool mips::MipsSymbol::isStringVar () const
{
    return size == mips::ASCII || size == mips::ASCIIZ;
}

bool mips::MipsSymbol::isAddressReg () const
{
    return type == mips::ADDRESS_REG;
}

bool mips::MipsSymbol::isVar () const
{
    return type == mips::VAR;
}

bool mips::MipsSymbol::isReg () const
{
    return type == mips::REG;
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

mips::MipsSymbol mips::MipsSymbol::makeReg (const std::string & reg, mips::MipsSymbolSize dataType)
{
    return { reg, mips::MipsSymbolType::REG, dataType };
}

mips::MipsSymbol mips::MipsSymbol::makeLabel (const std::string & label)
{
    return { label, mips::LABEL };
}

mips::MipsSymbol mips::MipsSymbol::makeVar (const std::string & name, mips::MipsSymbolSize dataType)
{
    return { name, mips::MipsSymbolType::VAR, dataType };
}

mips::MipsSymbol mips::MipsSymbol::makeAddressReg (const std::string & reg)
{
    return { reg, mips::MipsSymbolType::ADDRESS_REG, mips::WORD };
}