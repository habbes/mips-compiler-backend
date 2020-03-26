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
        if (statement.find("#end_function", 0) == 0)
        {
            return true;
        }
    }

    return false;
}

void IrParser::parseStatement(std::string & statement)
{

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