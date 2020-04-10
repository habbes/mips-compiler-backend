#include "mips_instruction.h"
#include <sstream>

std::string mipsOpToString(mips::MipsOp op);

bool mips::MipsInstruction::operator== (const mips::MipsInstruction & other) const
{
    if (op != other.op) return false;
    if (operands.size() != other.operands.size()) return false;

    for (auto i = 0; i < operands.size(); ++i)
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
    std::stringstream buffer;
    buffer << mipsOpToString(op);

    for (auto & operand : operands)
    {
        buffer << ", " << operand.name;
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
    }

    return "<unknown>";
}