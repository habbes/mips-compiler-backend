#include "mips_program.h"

mips::MipsFunction & mips::MipsProgram::newFunction(const std::string & name)
{
    auto func = std::make_unique<MipsFunction>(name);
    functions_.push_back(std::move(func));
    return currentFunction();
}

mips::MipsFunction & mips::MipsProgram::newFunction(const IrFunction & irFunc)
{
    auto func = std::make_unique<MipsFunction>(irFunc);
    functions_.push_back(std::move(func));
    return currentFunction();
}

mips::MipsFunction & mips::MipsProgram::currentFunction()
{
    int i = functions_.size() - 1;
    return *(functions_[i]);
}

mips::MipsFunction & mips::MipsProgram::operator [] (int i)
{
    return *(functions_[i]);
}

mips::MipsFunction & mips::MipsProgram::functionAt (int i)
{
    return *(functions_[i]);
}

int mips::MipsProgram::numFunctions () const
{
    return functions_.size();
}