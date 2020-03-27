#pragma once

#include <string>

constexpr const char * DTYPE_INT = "int";
constexpr const char * DTYPE_FLOAT = "float";

enum SymbolType
{
    TYPE,
    VAR,
    CONST,
    TARGET_LABEL,
    FUNC
};

struct SymbolInfo
{
    std::string name;
    SymbolType type;
    std::string dataType;
    int intValue = 0;
    float floatValue = 0;
    bool isArray = false;
    int arraySize = 0;

    bool operator==(const SymbolInfo & other) const;
    bool operator!=(SymbolInfo & other) const;
    std::string toString() const;
};

std::string symbolTypeToString(SymbolType type);
void tokenToSymbol (const std::string token, SymbolInfo & symbol);