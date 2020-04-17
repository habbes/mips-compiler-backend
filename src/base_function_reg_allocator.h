#pragma once

#include "ir_function.h"
#include "mips_function.h"

using mips::MipsFunction;

/**
 * base class for function-wide
 * register allocator
 */
class BaseFunctionRegAllocator
{
public:
    // called for each IR instruction, before the instruction is processed
    virtual void beforeInstruction(MipsFunction &, const IrFunction & irFunc, int irInst)
    {
    }

    // called for each IR instruction, after instruction has been processed
    virtual void afterInstruction(MipsFunction &, const IrFunction &irFunc, int IrInst)
    {
    }

    virtual ~BaseFunctionRegAllocator() = default;
};