#pragma once

#include <string>

constexpr const char * DTYPE_INT = "int";
constexpr const char * DTYPE_FLOAT = "float";

enum SymbolType
{
    TYPE,
    VAR,
    CONST,
    TARGET_LABEL
};

struct SymbolInfo
{
    std::string name;
    SymbolType type;
    std::string dataType;
    int intValue;
    float floatValue;

    bool operator==(SymbolInfo & other) const;
    bool operator!=(SymbolInfo & other) const;
    std::string toString() const;
};

std::string symbolTypeToString(SymbolType type);
void tokenToSymbol (std::string token, SymbolInfo & symbol);