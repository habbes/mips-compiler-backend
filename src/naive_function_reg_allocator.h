#pragma once

#include "ir_function.h"
#include "mips_function.h"
#include "base_function_reg_allocator.h"

class NaiveFunctionRegAllocator: public BaseFunctionRegAllocator
{
public:
    void afterInstruction(MipsFunction &, const IrFunction & irFunc, int irInst) override;
};