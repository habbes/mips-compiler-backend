#include "mips_instruction.h"
#include <sstream>

std::string mipsOpToString(mips::MipsOp op);

bool mips::MipsInstruction::operator== (const mips::MipsInstruction & other) const
{
    if (op != other.op) return false;
    if (operands.size() != other.operands.size()) return false;

    for (size_t i = 0; i < operands.size(); ++i)
    {
        if (operands[i] != other.operands[i]) return false;
    }
    return true;
}

bool mips::MipsInstruction::operator== (const std::string & other) const
{
    return toString() == other;
}

bool mips::MipsInstruction::operator!= (const mips::MipsInstruction & other) const
{
    return !(*this == other);
}

std::string mips::MipsInstruction::toString () const
{
    if (op == mips::MipsOp::INST_LABEL)
    {
        return operands[0].name + ":";
    }

    std::stringstream buffer;
    buffer << mipsOpToString(op);

    for (size_t i = 0; i < operands.size(); i++)
    {
        buffer << (i == 0 ? " " : ", ");
        buffer << operands[i].name;
    }
    
    return buffer.str();
}


std::string mipsOpToString (mips::MipsOp op)
{
    switch (op)
    {
        case mips::MipsOp::LW:
            return "lw";
        case mips::MipsOp::LI:
            return "li";
        case mips::MipsOp::LA:
            return "la";
        case mips::MipsOp::LB:
            return "lb";
        case mips::MipsOp::LBU:
            return "lbu";
        case mips::MipsOp::LHU:
            return "lhu";
        case mips::MipsOp::LH:
            return "lh";
        case mips::MipsOp::SW:
            return "sw";
        case mips::MipsOp::ADD:
            return "add";
        case mips::MipsOp::SUB:
            return "sub";
        case mips::MipsOp::MUL:
            return "mul";
        case mips::MipsOp::JR:
            return "jr";
    }

    return "<unknown>";
}