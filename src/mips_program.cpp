#include "mips_program.h"

void writeIndent(std::ostream & out);
void writeLine(std::ostream & out, const std::string & s = "");
void writeIndentedLine(std::ostream & out, const std::string & s = "");

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

mips::MipsFunction & mips::MipsProgram::currentFunction() const
{
    int i = functions_.size() - 1;
    return *(functions_[i]);
}

mips::MipsFunction & mips::MipsProgram::operator[] (int i) const
{
    return *(functions_[i]);
}

mips::MipsFunction & mips::MipsProgram::functionAt (int i) const
{
    return *(functions_[i]);
}

int mips::MipsProgram::numFunctions () const
{
    return functions_.size();
}

void mips::MipsProgram::write (std::ostream & out) const
{
    std::string indent = "  ";
    auto & func = functionAt(0);

    // data segment
    out << indent << ".data" << std::endl;
    for (auto & item : func.vars())
    {
        out << item.second.name << ":"
            << indent
            << '.' << item.second.sizeString()
            << indent
            << func.initialValues().at(item.second.name)
            << std::endl;
    }

    // text segment
    out << indent << ".text" << std::endl;
    // out << func.name() << ":" << std::endl;
    for (int i = 0; i < func.numInstructions(); i++)
    {
        auto & inst = func.instruction(i);
        if (inst.op != mips::MipsOp::INST_LABEL)
        {
            out << indent;
        }
        out << inst.toString() << std::endl;
    }

}

void writeIndent(std::ostream & out)
{
    out << "  ";
}

void writeLine(std::ostream & out, const std::string & s)
{
    out << s << std::endl;
}

void writeIndentedLine(std::ostream & out, const std::string & s)
{
    writeIndent(out);
    writeLine(out, s);
}