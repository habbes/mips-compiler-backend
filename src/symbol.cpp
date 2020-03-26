#include "symbol.h"
#include <sstream>

bool SymbolInfo::operator== (SymbolInfo & other) const
{
    return name == other.name
        && dataType == other.dataType
        && type == other.type;
}

bool SymbolInfo::operator!= (SymbolInfo & other) const
{
    return !(*this == other);
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
        case SymbolType::CONST: return "const";
        case SymbolType::TARGET_LABEL: return "label";
    }

    return "unknownType:" + std::to_string(type);
}

void tokenToSymbol (std::string token, SymbolInfo & symbol)
{
    symbol.name = token;

    char *invalidPtr;
    auto parsedLong = std::strtol(token.c_str(), &invalidPtr, 10);
    if (!*invalidPtr)
    {
        symbol.type = SymbolType::CONST;
        symbol.dataType = DTYPE_INT;
        symbol.intValue = (int) parsedLong;
        return;
    }

    auto parsedDouble = std::strtod(token.c_str(), &invalidPtr);
    if (!*invalidPtr)
    {
        symbol.type = SymbolType::CONST;
        symbol.dataType = DTYPE_FLOAT;
        symbol.floatValue = (float) parsedDouble;
        return;
    }

    symbol.type = SymbolType::VAR;
    return;
}