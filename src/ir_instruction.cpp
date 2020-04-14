#include "ir_instruction.h"
#include <sstream>

// IrInstruction

bool IrInstruction::operator== (IrInstruction & other) const
{
    if (op != other.op) return false;
    if (params.size() != other.params.size()) return false;

    for (size_t i = 0; i < params.size(); ++i)
    {
        if (params[i] != other.params[i]) return false;
    }
    return true;
}

bool IrInstruction::operator!= (IrInstruction & other) const
{
    return !(*this == other);
}

const SymbolInfo & IrInstruction::label () const
{
    switch (op)
    {
        case OpCode::BREQ:
        case OpCode::BRGT:
        case OpCode::BRGEQ:
        case OpCode::BRLT:
        case OpCode::BRLEQ:
        case OpCode::BRNEQ:
            return params[2];
        case OpCode::GOTO:
        case OpCode::LABEL:
            return params[0];
        default:
            // should return error
            return params[0];
    }
}

bool IrInstruction::isBranch () const
{
    return isConditionalBranch() || isUnconditionalBranch();
}

bool IrInstruction::isConditionalBranch () const
{
    return op == OpCode::BREQ
        || op == OpCode::BRGEQ
        || op == OpCode::BRGT
        || op == OpCode::BRLEQ
        || op == OpCode::BRLT
        || op == OpCode::BRNEQ;
}

bool IrInstruction::isUnconditionalBranch () const
{
    return op == OpCode::GOTO;
}

bool IrInstruction::isLabel () const
{
    return op == OpCode::LABEL;
}

bool IrInstruction::isLabel () const
{
    return op == OpCode::CALL || op == OpCode::CALLR;
}

std::string IrInstruction::toString () const
{
    std::stringstream buffer;
    buffer << op;
    for (auto param : params)
    {
        buffer << ',' << param.name;
    }
    return buffer.str();
}

// end IrInstruction


// IrInstructionBuilder

IrInstructionBuilder::IrInstructionBuilder (OpCode op)
{
    instruction_ = std::make_unique<IrInstruction>();
    instruction_->op = op;
}

IrInstructionBuilder IrInstructionBuilder::fromOp (OpCode op)
{
    IrInstructionBuilder builder(op);
    return builder;
}

IrInstructionBuilder & IrInstructionBuilder::param (SymbolInfo symbol)
{
    instruction_->params.push_back(symbol);
    return *this;
}

IrInstructionUPtr IrInstructionBuilder::build ()
{
    return std::move(instruction_);
}

// end IrInstructionBuilder

OpCode stringToOpCode(const std::string & text)
{
    if (text == "assign") return OpCode::ASSIGN;
    if (text == "add") return OpCode::ADD;
    if (text == "sub") return OpCode::SUB;
    if (text == "mul") return OpCode::MULT;
    if (text == "mult") return OpCode::MULT;
    if (text == "div") return OpCode::DIV;
    if (text == "and") return OpCode::AND;
    if (text == "or") return OpCode::OR;
    if (text == "goto") return OpCode::GOTO;
    if (text == "breq") return OpCode::BREQ;
    if (text == "brneq") return OpCode::BRNEQ;
    if (text == "brlt") return OpCode::BRLT;
    if (text == "brgt") return OpCode::BRGT;
    if (text == "brgeq") return OpCode::BRGEQ;
    if (text == "brleq") return OpCode::BRLEQ;
    if (text == "return") return OpCode::RETURN;
    if (text == "call") return OpCode::CALL;
    if (text == "callr") return OpCode::CALLR;
    if (text == "array_store") return OpCode::ARRAY_STORE;
    if (text == "array_load") return OpCode::ARRAY_LOAD;

    return OpCode::INVALID;
}