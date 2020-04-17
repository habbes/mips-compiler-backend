#pragma once

#include "base_reg_allocator.h"
#include "block_function_reg_allocator.h"

class BlockRegAllocator: public BaseRegAllocator
{
public:
    FunctionRegAllocatorPtr getFunctionAllocator(const IrFunction & irFunc) override
    {
        return std::move(std::make_unique<BlockFunctionRegAllocator>(irFunc));
    }
};