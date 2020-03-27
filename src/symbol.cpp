#include "symbol.h"
#include <sstream>

bool SymbolInfo::operator== (const SymbolInfo & other) const
{
    return name == other.name
        && dataType == other.dataType
        && type == other.type
        && isArray == other.isArray
        && arraySize == other.arraySize;
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
        << ",a:" << isArray
        << ",as:" << arraySize
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
        case SymbolType::FUNC: return "func";
    }

    return "unknownType:" + std::to_string(type);
}

void tokenToSymbol (const std::string token, SymbolInfo & symbol)
{
    symbol.name = token;
    symbol.arraySize = 0;
    symbol.isArray = false;

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

    size_t subscriptPos = token.find('[');
    if (subscriptPos != std::string::npos)
    {
        // this is an array
        symbol.name = token.substr(0, subscriptPos);
        std::string arraySize = token.substr(subscriptPos + 1);
        arraySize = arraySize.substr(0, arraySize.size() - 1);
        symbol.isArray = true;
        symbol.arraySize = (int) std::strtol(arraySize.c_str(), &invalidPtr, 10);
    }

    symbol.type = SymbolType::VAR;
    return;
}