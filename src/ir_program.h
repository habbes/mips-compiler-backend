#pragma once

#include <vector>
#include <memory>
#include "ir_function.h"

class IrProgram
{
    std::vector<std::unique_ptr<IrFunction>> functions_;
    std::vector<int> findLeaders();
public:
    IrFunction &newFunction(const std::string &);
    IrFunction &currentFunction();
    IrFunction &operator [](int i);
    int numFunctions() const;
};