#include "mips_symbol.h"

bool mips::MipsSymbol::operator== (const MipsSymbol & other) const
{
    return type == other.type
        && size == other.size
        && label == other.label
        && constValue == other.constValue
        && reg == other.reg;
}

bool mips::MipsSymbol::operator!= (const MipsSymbol & other) const
{
    return !(*this == other);
}
