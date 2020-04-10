#include "mips_function.h"

mips::MipsFunction::MipsFunction (const std::string & name): name_(name) {}

mips::MipsFunction::MipsFunction (const IrFunction & irFunc)
{
    name_ = irFunc.name();
    for (auto & item: irFunc.vars())
    {
        auto & irVar = item.second;
        if (irVar.type == SymbolType::VAR)
        {
            mips::MipsSymbol mipsVar = {
                .name = irVar.name,
                .type = mips::MipsSymbolType::VAR,
                .size = irVar.dataType == DTYPE_INT ? mips::MipsSymbolSize::WORD : mips::MipsSymbolSize::FLOAT
            };

            addVar(mipsVar, "0");
        }
    }
}

void mips::MipsFunction::addVar (const mips::MipsSymbol &var, const std::string & initialValue)
{
    vars_.insert_or_assign(var.name, var);
    initialValues_.insert_or_assign(var.name, initialValue);
}

void mips::MipsFunction::addInstruction (mips::MipsInstructionUPtr instruction)
{
    instructions_.push_back(std::move(instruction));
}

std::string mips::MipsFunction::name () const
{
    return name_;
}

const mips::MipsVarMap & mips::MipsFunction::vars () const
{
    return vars_;
}