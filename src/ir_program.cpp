#include "ir_program.h"


IrFunction & IrProgram::newFunction(const std::string & name)
{
    auto func = std::make_unique<IrFunction>(name);
    functions_.push_back(std::move(func));
    return currentFunction();
}

IrFunction & IrProgram::currentFunction()
{
    int i = functions_.size() - 1;
    return *(functions_[i]);
}

IrFunction & IrProgram::operator [] (int i)
{
    return *(functions_[i]);
}

int IrProgram::numFunctions() const
{
    return functions_.size();
}
