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

bool mips::MipsInstruction::isLabel () const
{
    return op == mips::MipsOp::INST_LABEL;
}

const mips::MipsSymbol & mips::MipsInstruction::label () const
{
    if (isLabel()) return operands[0];
    return operands[1];
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
        case mips::MipsOp::DIV:
            return "div";
        case mips::MipsOp::BEQ:
            return "beq";
        case mips::MipsOp::BNE:
            return "bne";
        case mips::MipsOp::BLT:
            return "blt";
        case mips::MipsOp::BLE:
            return "ble";
        case mips::MipsOp::BGT:
            return "bgt";
        case mips::MipsOp::BGE:
            return "bge";
        case mips::MipsOp::JR:
            return "jr";
        case mips::MipsOp::J:
            return "j";
        case mips::MipsOp::JAL:
            return "jal";
        case mips::MipsOp::SYSCALL:
            return "syscall";
    }

    char buf[100];
    sprintf(buf, "<unkown:%d>", op);
    return std::string(buf);
}