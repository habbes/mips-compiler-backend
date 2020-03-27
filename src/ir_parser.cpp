#include <string>
#include <istream>
#include <sstream>
#include <memory>
#include "ir_parser.h"
#include "helpers.h"

IrParser::IrParser (std::istream & source): source_(source)
{
    program_ = std::make_unique<IrProgram>();
}

IrProgram & IrParser::program() const
{
    return *program_;
}

void IrParser::parse ()
{
    while(parseFunction());
}

bool IrParser::parseFunction()
{   
    std::string statement;
    auto res = readNextStatement(statement);
    if (!res) return false;

    std::vector<std::string> headerTokens;
    getTokens(statement, headerTokens);
    if (!res || headerTokens[0] != "#start_function") return false;

    program_->newFunction(headerTokens[1]);

    if (!parseFunctionSignature()) return false;
    if (!parseIntList()) return false;
    if (!parseFloatList()) return false;
    if (!parseFunctionBody()) return false;

    return true;
}

bool IrParser::parseFunctionSignature()
{
    std::string statement;
    auto res = readNextStatement(statement);
    if (!res) return false;

    std::stringstream stream(statement);

    // read return type
    std::string returnTypeName;
    getNextToken(stream, returnTypeName);
    SymbolInfo returnType = { .name = returnTypeName, .type = SymbolType::TYPE };
    program_->currentFunction().setReturnType(returnType);

    // read name
    std::string funcName;
    getNextToken(stream, funcName, '(');

    // read params
    std::vector<std::string> params;
    std::vector<std::string> paramPair(2);
    getTokens(stream, params, ',', ")");
    for (auto & param : params)
    {
        paramPair.clear();
        // last param will be attached to ), so let's strip it
        if (param[param.size() - 1] == ')')
        {
            std::string temp = param.substr(0, param.size() - 1);
            param = trim(temp);
        }

        getTokens(param, paramPair);
        SymbolInfo paramSymbol = { .name = paramPair[1], .type = SymbolType::VAR, .dataType = paramPair[0] };
        program_->currentFunction().addParam(paramSymbol);
    }
    
    return true;
}

bool IrParser::parseIntList()
{
    return parseVarList(DTYPE_INT);
}

bool IrParser::parseFloatList()
{
    return parseVarList(DTYPE_FLOAT);
}

bool IrParser::parseVarList(const std::string & dataType)
{
    std::string statement;
    if (!readNextStatement(statement)) return false;

    std::stringstream stream(statement);

    // read int-list or float-list:
    std::string header;
    getNextToken(stream, header);

    std::vector<std::string> varNames;
    getTokens(stream, varNames, ',');

    for (auto & name: varNames)
    {
        SymbolInfo var = { .name = name, .type = SymbolType::VAR, .dataType = dataType };
        program_->currentFunction().addVar(var);
    }

    return true;
}


bool IrParser::parseFunctionBody()
{
    std::string statement;
    while (readNextStatement(statement))
    {
        if (statement.find("#end_function", 0) == 0) return true;
        if (!parseStatement(statement)) return false;
    }

    return false;
}

bool IrParser::parseStatement(std::string & statement)
{
    TokenList tokens;
    getTokens(statement, tokens, ',');
    if (tokens.size() == 0) return false;

    if (*(tokens[0].cend() - 1) == ':')
    {
        // this is a label
        SymbolInfo symbol = { .name = tokens[0].substr(0, tokens[0].size() - 1), .type = SymbolType::TARGET_LABEL };
        program_->currentFunction().addInstruction(IrInstructionBuilder::fromOp(OpCode::LABEL).param(symbol).build());
        return true;
    }

    OpCode op = stringToOpCode(tokens[0]);
    IrInstructionBuilder builder(op);
    
    for (auto i = 1; i < tokens.size(); i++)
    {
        SymbolInfo symbol;
        tokenToSymbol(tokens[i], symbol);
        if (op == OpCode::CALL && i == 1)
        {
            symbol.type = SymbolType::FUNC;
        }
        else if (symbol.type == SymbolType::VAR)
        {
            if (program_->currentFunction().vars().count(symbol.name) > 0)
            {
                symbol = program_->currentFunction().vars().at(symbol.name);
            }
            else
            {
                symbol.type = SymbolType::TARGET_LABEL;
            }
        }
        builder.param(symbol);
    }

    program_->currentFunction().addInstruction(builder.build());
    return true;
}

bool IrParser::readNextStatement(std::string & nextStatement)
{
    while (getline(source_, nextStatement))
    {
        nextStatement = trim(nextStatement);
        if (!nextStatement.empty())
        {
            return true;
        }
    }
    return false;
}