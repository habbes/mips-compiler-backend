#include "ir_function.h"

IrFunction::IrFunction(const std::string & name): name_(name)
{}

const std::string &IrFunction::name() const
{
    return name_;
}

void IrFunction::setName(std::string & name)
{
    name_ = name;
}

const SymbolInfo & IrFunction::returnType() const
{
    return returnType_;
}

void IrFunction::setReturnType(SymbolInfo returnType)
{
    returnType_ = returnType;
}

void IrFunction::addParam(SymbolInfo param)
{
    params_.push_back(param);
}

const ParamList & IrFunction::params() const
{
    return params_;
}

void IrFunction::addVar(SymbolInfo var)
{
    vars_.insert_or_assign(var.name, var);
}

const VarMap & IrFunction::vars() const
{
    return vars_;
}