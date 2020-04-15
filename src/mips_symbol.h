#pragma once

#include <string>

namespace mips
{

enum MipsSymbolType
{
    REG,
    LABEL,
    VAR,
    CONST,
    ADDRESS_REG
};

enum MipsSymbolSize
{
    WORD,
    HALF,
    BYTE,
    FLOAT,
    DOUBLE,
    SPACE,
    ASCII,
    ASCIIZ
};


struct MipsSymbol
{
    std::string name;
    MipsSymbolType type;
    MipsSymbolSize size;

    bool operator==(const MipsSymbol & other) const;
    bool operator!=(const MipsSymbol & other) const;
    bool isStringVar() const;
    bool isAddressReg() const;
    std::string toString() const;
    std::string sizeString() const;
    static MipsSymbol makeConst(int value);
    static MipsSymbol makeReg (const std::string & reg, mips::MipsSymbolSize dataType = mips::WORD);
    static MipsSymbol makeLabel(const std::string & label);
    static MipsSymbol makeVar(const std::string & name, mips::MipsSymbolSize dataType = mips::WORD);
    static MipsSymbol makeAddressReg(const std::string & reg);
};

}