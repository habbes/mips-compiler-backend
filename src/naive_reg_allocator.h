#pragma once

#include "base_reg_allocator.h"

class NaiveRegAllocator: public BaseRegAllocator
{
public:
    FunctionRegAllocatorPtr getFunctionAllocator(const IrFunction &)
    {
        return std::move(std::make_unique<BaseFunctionRegAllocator>());
    }
};