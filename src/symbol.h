#pragma once

#include <string>

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
};

