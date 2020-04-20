#pragma once

namespace mips
{

// hardwired to 0
constexpr const char * REG_ZERO = "$zero";
// reserved for pseudo instructions
constexpr const char * REG_AT = "$at";
// return values from functions
constexpr const char * REG_V0 = "$v0";
constexpr const char * REG_V1 = "$v1";
// args to functions - not preserved
constexpr const char * REG_A0 = "$a0";
constexpr const char * REG_A1 = "$a1";
constexpr const char * REG_A2 = "$a2";
constexpr const char * REG_A3 = "$a3";
// temporary data - not preserved
constexpr const char * REG_T0 = "$t0";
constexpr const char * REG_T1 = "$t1";
constexpr const char * REG_T2 = "$t2";
constexpr const char * REG_T3 = "$t3";
constexpr const char * REG_T4 = "$t4";
constexpr const char * REG_T5 = "$t5";
constexpr const char * REG_T6 = "$t6";
constexpr const char * REG_T7 = "$t7";
// saved registers - preserved
constexpr const char * REG_S0 = "$s0";
constexpr const char * REG_S1 = "$s1";
constexpr const char * REG_S2 = "$s2";
constexpr const char * REG_S3 = "$s3";
constexpr const char * REG_S4 = "$s4";
constexpr const char * REG_S5 = "$s5";
constexpr const char * REG_S6 = "$s6";
constexpr const char * REG_S7 = "$s7";
// more temporary registers - not preserved
constexpr const char * REG_T8 = "$t8";
constexpr const char * REG_T9 = "$t9";
// preserved for kernel, do not use
constexpr const char * REG_K0 = "$k0";
constexpr const char * REG_K1 = "$k1";
// global area pointer (base of global data segment)
constexpr const char * REG_GP = "$gp";
// stack pointer
constexpr const char * REG_SP = "$sp";
// frame pointer
constexpr const char * REG_FP = "$fp";
// return address
constexpr const char * REG_RA = "$ra";

// FLOATING POINT registers

// floating point return values
constexpr const char * REG_F0 = "$f0";
constexpr const char * REG_F1 = "$f1";
constexpr const char * REG_F2 = "$f2";
constexpr const char * REG_F3 = "$f3";
// temporary registers, not preserved
constexpr const char * REG_F4 = "$f4";
constexpr const char * REG_F5 = "$f5";
constexpr const char * REG_F6 = "$f6";
constexpr const char * REG_F7 = "$f7";
constexpr const char * REG_F8 = "$f8";
constexpr const char * REG_F9 = "$f9";
constexpr const char * REG_F10 = "$f10";
// first 2 arguments to subprograms, not preserved (TODO: Is this correct? There are 3 registers)
constexpr const char * REG_F12 = "$f12";
constexpr const char * REG_F13 = "$f13";
constexpr const char * REG_F14 = "$f14";
// more temporary registers
constexpr const char * REG_F16 = "$f16";
constexpr const char * REG_F17 = "$f17";
constexpr const char * REG_F18 = "$f18";
// saved registers, preserved
constexpr const char * REG_F20 = "$f20";
constexpr const char * REG_F21 = "$f21";
constexpr const char * REG_F22 = "$f22";
constexpr const char * REG_F23 = "$f23";
constexpr const char * REG_F24 = "$f24";
constexpr const char * REG_F25 = "$f25";
constexpr const char * REG_F26 = "$f26";
constexpr const char * REG_F27 = "$f27";
constexpr const char * REG_F28 = "$f28";
constexpr const char * REG_F29 = "$f29";
constexpr const char * REG_F30 = "$f30";
constexpr const char * REG_F31 = "$f31";

// persistent registers that we can allocate to variables
constexpr const char* PERSISTENT_REGS[] = { REG_S0, REG_S1, REG_S2, REG_S3, REG_S4, REG_S5, REG_S6, REG_S7 };
constexpr const int NUM_PERSISTENT_REGS = 8;

}