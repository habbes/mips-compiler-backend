#pragma once

#include <memory>
#include "base_function_reg_allocator.h"

/**
 * base class for program-wide register allocator
 */
class BaseRegAllocator
{
public:
    std::unique_ptr<BaseFunctionRegAllocator> getFunctionAllocator(const IrFunction &);
};