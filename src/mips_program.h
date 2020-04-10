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
    MipsFunction &functionAt(int i) const;
    MipsFunction &operator [](int i) const;
    MipsFunction &currentFunction() const;
    int numFunctions() const;
};

}