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
            if (irVar.isArray)
            {
                // allocate space for array
                auto elementSize = irVar.dataType == DTYPE_INT ? 4 : 8;
                auto totalSize = irVar.arraySize * elementSize;
                addVar(mips::MipsSymbol::makeVar(irVar.name, mips::MipsSymbolSize::SPACE),
                    std::to_string(totalSize));
            }
            else
            {
                auto mipsDataType = irVar.dataType == DTYPE_INT ?
                    mips::MipsSymbolSize::WORD : mips::MipsSymbolSize::FLOAT;
                addVar(mips::MipsSymbol::makeVar(irVar.name, mipsDataType), "0");
            }
        }
    }

    if (irFunc.makesCalls())
    {
        backupRa_ = true;
        raBackupVarName_ = name_ + "_saved_ra_";
        addVar(mips::MipsSymbol::makeVar(raBackupVarName_, mips::WORD), "0");
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

void mips::MipsFunction::addCodeComment (const std::string & comment)
{
    int pos = instructions_.size();
    codeComments_.insert_or_assign(pos, comment);
}

const mips::MipsCommentList & mips::MipsFunction::codeComments () const
{
    return codeComments_;
}

bool mips::MipsFunction::backsUpRa () const
{
    return backupRa_;
}

std::string mips::MipsFunction::backupRaVarName () const
{
    return raBackupVarName_;
}

const mips::MipsSymbol & mips::MipsFunction::backupRaVar () const
{
    return vars_.at(raBackupVarName_);
}