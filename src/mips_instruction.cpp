#include "mips_instruction.h"

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

bool mips::MipsInstruction::operator!= (const mips::MipsInstruction & other) const
{
    return !(*this == other);
}