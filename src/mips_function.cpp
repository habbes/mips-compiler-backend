#include "mips_function.h"
#include <memory>

mips::MipsFunction::MipsFunction (const std::string & name): name_(name) {}

mips::MipsFunction::MipsFunction (const IrFunction & irFunc)
{
    name_ = irFunc.name();
    for (auto & item: irFunc.vars())
    {
        auto & irVar = item.second;
        if (irVar.type == SymbolType::VAR)
        {
            auto mipsDataType = irVar.dataType == DTYPE_INT ?
                mips::MipsSymbolSize::WORD : mips::MipsSymbolSize::FLOAT;
            addVar(mips::MipsSymbol::makeVar(irVar.name, mipsDataType), "0");
        }
    }
}

void mips::MipsFunction::addVar (const mips::MipsSymbol &var, const std::string & initialValue)
{
    vars_.insert_or_assign(var.name, var);
    initialValues_.insert_or_assign(var.name, initialValue);
}

void mips::MipsFunction::addInstruction (mips:: MipsInstruction instruction)
{
    instructions_.push_back(std::make_unique<mips::MipsInstruction>(std::move(instruction)));
}

const mips::MipsInstruction & mips::MipsFunction::instruction (int i) const
{
    return *instructions_[i];
}

int mips::MipsFunction::numInstructions () const
{
    return instructions_.size();
}

std::string mips::MipsFunction::name () const
{
    return name_;
}

const mips::MipsVarMap & mips::MipsFunction::vars () const
{
    return vars_;
}

const mips::MipsInitVals & mips::MipsFunction::initialValues () const
{
    return initialValues_;
}