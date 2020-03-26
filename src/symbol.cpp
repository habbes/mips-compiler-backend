#include "symbol.h"
#include <sstream>

bool SymbolInfo::operator== (SymbolInfo & other) const
{
    return name == other.name
        && dataType == other.dataType
        && type == other.type;
}

std::string SymbolInfo::toString () const
{
    std::stringstream buffer;
    buffer << "Symbol(n:" << name
        << ",t:" << symbolTypeToString(type)
        << ",dt:" << dataType
        << ")";

    return buffer.str();
}


std::string symbolTypeToString (SymbolType type)
{
    switch (type)
    {
        case SymbolType::TYPE: return "type";
        case SymbolType::VAR: return "var";
    }

    return "unknownType:" + std::to_string(type);
}