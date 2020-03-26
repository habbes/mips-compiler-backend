#pragma once

#include <string>

constexpr const char * DTYPE_INT = "int";
constexpr const char * DTYPE_FLOAT = "float";

enum SymbolType
{
    TYPE,
    VAR
};

struct SymbolInfo
{
    std::string name;
    SymbolType type;
    std::string dataType;
    bool operator==(SymbolInfo & other) const;
    std::string toString() const;
};

std::string symbolTypeToString(SymbolType type);