#pragma once

#include "ir_function.h"
#include "mips_function.h"

class Ir2Mips;

using mips::MipsFunction;

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

    virtual ~BaseFunctionRegAllocator() = default;
};