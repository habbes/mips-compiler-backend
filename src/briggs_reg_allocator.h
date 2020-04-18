#pragma once

#include "base_reg_allocator.h"
#include "briggs_function_reg_allocator.h"

class BriggsRegAllocator: public BaseRegAllocator
{
public:
    FunctionRegAllocatorPtr getFunctionAllocator(const IrFunction & irFunc) override
    {
        return std::make_unique<BriggsFunctionRegAllocator>(irFunc);
    }
};