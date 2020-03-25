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
    std::stringstream stream(statement);
    getTokens(stream, headerTokens);
    if (!res || headerTokens[0] != "#start_function") return false;

    program_->newFunction(headerTokens[1]);

    if (!parseFunctionSignature()) return false;

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

        std::stringstream paramStream(param);
        getTokens(paramStream, paramPair);
        SymbolInfo paramSymbol = { .name = paramPair[1], .type = SymbolType::VAR, .dataType = paramPair[0] };
        program_->currentFunction().addParam(paramSymbol);
    }
    
    return true;
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