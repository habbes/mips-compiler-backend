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
    for (int i = 0; i < numFunctions(); i++)
    {
        writeFunctionAt(i, out);
        out << std::endl;
    }
}

void mips::MipsProgram::writeFunctionAt (int funcIndex, std::ostream & out) const
{
    std::string indent = "  ";
    auto & func = functionAt(funcIndex);

    // data segment
    out << "### " << func.name() << " ###" << std::endl;
    out << func.name() << ":" << std::endl;
    out << indent << ".data" << std::endl;
    for (auto & item : func.vars())
    {
        auto & var = item.second;
        std::string origValue = func.initialValues().at(var.name);

        out << var.name << ":"
            << indent
            << '.' << var.sizeString()
            << indent;
        if (var.isStringVar())
        {
            out << "\"";
            for (auto c : origValue)
            {
                if (c == '\n') out << "\\n";
                else out << c;
            }
            out << "\"";
        }
        else
        {
            out << origValue;
        }

        out << std::endl;
    }

    // text segment
    auto comments = func.codeComments();
    out << indent << ".text" << std::endl;
    for (int i = 0; i < func.numInstructions(); i++)
    {
        auto comment = comments.find(i);
        if (comment != comments.end())
        {
            out << "# " << comment->second << std::endl;
        }
        auto & inst = func.instruction(i);
        if (inst.isLabel() && inst.label().name == func.name())
        {
            // function name label has already been added at the top, don't duplicate
            continue;
        }
        if (!inst.isLabel())
        {
            out << indent;
        }
        out << inst.toString() << std::endl;
    }
}
