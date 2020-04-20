#pragma once

#include "ir_function.h"
#include "mips_function.h"

class Ir2Mips;

using mips::MipsFunction;
using mips::MipsSymbol;

/**
 * base class for function-wide
 * register allocator
 */
class BaseFunctionRegAllocator
{
public:
    // called for each IR instruction, before the instruction is processed
    virtual void beforeInstruction(Ir2Mips & compiler, int irInst)
    {
    }

    // called for each IR instruction, after instruction has been processed
    virtual void afterInstruction(Ir2Mips & compiler, int IrInst)
    {
    }

    // returns the register allocated for the specified var if any
    // otherwise, returns the var itself
    // isDef is true when the var is being assigned and false when it's value is being used
    virtual MipsSymbol getRegIfAllocated(const MipsSymbol & var, int irIndex, bool isDef = false)
    {
        return var;
    }

    virtual ~BaseFunctionRegAllocator() = default;
};