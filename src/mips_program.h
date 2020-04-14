#pragma once

#include <ostream>
#include "mips_function.h"

namespace mips
{
    
class MipsProgram
{
    std::vector<std::unique_ptr<MipsFunction>> functions_;
    
    void writeFunctionAt(int funcIndex, std::ostream & out) const;
public:
    MipsFunction &newFunction(const std::string &);
    MipsFunction &newFunction(const IrFunction &);
    MipsFunction &functionAt(int i) const;
    MipsFunction &operator [](int i) const;
    MipsFunction &currentFunction() const;
    int numFunctions() const;
    void write(std::ostream & out) const;
};

}