#pragma once

#include <string>

struct BasicBlock
{
    int id;
    int first;
    int last;

    bool operator==(const BasicBlock & other) const;
    std::string toString() const;
};