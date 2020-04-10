#pragma once

#include "mips_function.h"

namespace mips
{
    
class MipsProgram
{
    std::vector<std::unique_ptr<MipsFunction>> functions_;
public:
    MipsFunction &newFunction(const std::string &);
    MipsFunction &newFunction(const IrFunction &);
    MipsFunction &functionAt(int i);
    MipsFunction &operator[](int i);
    MipsFunction &currentFunction();
    int numFunctions() const;
};

}