#pragma once

#include <vector>
#include <string>
#include "mips_symbol.h"

namespace mips
{

enum MipsOp
{
    /* Integer ALU operations */
    // $op1 = $op2 + $op3, exception for signed
    ADD,
    // $op1 = $op2 + $op3 no exception for signed
    ADDU,
    // $s1 = $op2 - $op3
    SUB,
    // $op1 = $op2 * $op3
    MUL,
    // $op1 = $op2
    MOVE,
    // $op1 = $op2 + const
    ADDI,
    // $op1 = $op2 | const
    ORI,
    // $op1 = $op2 & const
    ANDI,

    /* Integer Load and Store */
    // lw $t0, label -> load 32bit word at label to $t0
    LW,
    // lb $t0, label -> Load sign-extended byte at label to $t0
    LB,
    // lbu $t0, label -> Load 0-extended byte at label to $t0
    LBU,
    // lh $t0, label -> Load sign-extended halfword (16 bits)
    LH,
    // lhu $t0, label # Load 0-extended halfword (16 bits)
    LHU,
    // li $t0, value # Load 32-bit constant to $t0
    LI,
    // la $t0, label # Load ADDRESS of label
    LA,
    // sw $t0, label # The only instruction that has destination
    SW,

    /* Jump and Branch */
    // j label -> unconditional jump
    J,
    // beq $t0, $t1, label -> Branch if $t0 == $t1
    BEQ,
    // blt $t0, $t1, label -> Branch if $t0 < $t1
    BLT,
    // jr $ra -> return to calling program
    JR,

    /* Calls */
    // System call
    SYSCALL,

    /* MISC */
    INST_LABEL,
    INVALID = -1
};

struct MipsInstruction
{
    MipsOp op;
    std::vector<MipsSymbol> operands;

    bool operator==(const MipsInstruction & other) const;
    bool operator==(const std::string & other) const;
    bool operator!=(const MipsInstruction & other) const;
    std::string toString() const;
};

}