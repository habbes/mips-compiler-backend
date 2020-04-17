#pragma once

#include <memory>
#include "base_function_reg_allocator.h"

typedef BaseFunctionRegAllocator * FunctionRegAllocatorPtr;

/**
 * base class for program-wide register allocator
 */
class BaseRegAllocator
{
public:
    virtual FunctionRegAllocatorPtr getFunctionAllocator(const IrFunction &) = 0;
    virtual ~BaseRegAllocator() = default;
};