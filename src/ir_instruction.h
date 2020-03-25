#pragma once

#include <string>
#include <vector>
#include "symbol.h"

enum OpCode
{

};

struct IrInstruction
{
    OpCode op;
    std::string name;
    std::vector<SymbolInfo> params;
};