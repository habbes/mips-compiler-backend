#pragma once

#include <string>

namespace mips
{
// MIPS registers
enum MipsReg
{
    // hardwired to 0
    ZERO,
    // reserved for pseudo-instructions
    AT,
    // return values from functions
    V0, V1,
    // args to functions - not preserved by subprograms
    A0, A1, A2, A3,
    // temporary data - not preserved by suprograms
    T0, T1, T2, T3, T4, T5, T6, T7,
    // saved registers, preserved by subprograms
    S0, S1, S2, S3, S4, S5, S6, S7,
    // more temp registers, not preserved
    T8, T9,
    // preserved for kernel, do not use
    K0, K1,
    // global area pointer (base of global data segment)
    GP,
    // stack pointer
    SP,
    // frame pointer
    FP,
    // return address
    RA,
    
    // floating point return values
    F0, F1, F2, F3,
    // temp float registers, not preserved
    F4, F5, F6, F7, F8, F9, F10,
    // first two args to subprograms, not preserved
    F12, F13, F14,
    // temp float registers, not preserved
    F16, F17, F18,
    // saved registers, preserved
    F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

enum MipsSymbolType
{
    REG,
    LABEL,
    VAR,
    CONST
};

// union MipsSymbolValue
// {
//     MipsReg reg;
//     int number;
//     std::string name;
//     ~MipsSymbolValue() {}
//     MipsSymbolValue() = default;
//     MipsSymbolValue(const MipsSymbolValue &other)
//     {
//         reg = other.reg;
//         number = other.number;
//         name = other.name;
//     }
// };

enum MipsSymbolSize
{
    WORD,
    HALF,
    BYTE,
    FLOAT,
    DOUBLE,
    SPACE,
    ASCII,
    ASCIIZ
};


struct MipsSymbol
{
    std::string name;
    MipsSymbolType type;
    MipsSymbolSize size;

    bool operator==(const MipsSymbol & other) const;
    bool operator!=(const MipsSymbol & other) const;
    std::string toString() const;
};
}