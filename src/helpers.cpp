#include "helpers.h"

#include <string>
#include <sstream>

bool getNextToken(std::istream & source, std::string & token, char delim)
{
    while (std::getline(source, token, delim))
    {
        token = trim(token);
        if (!token.empty())
        {
            return true;
        }
    }
    return false;
}

bool getNextToken(std::string & source, std::string & token, char delim)
{
    std::stringstream stream(source);
    return getNextToken(static_cast<std::istream &>(stream), token, delim);
}

void getTokens(std::stringstream & source, TokenList & tokens, char delim, const std::string & stopAt)
{
    std::string token;
    while (getNextToken(source, token, delim))
    {
        if (!stopAt.empty() && token == stopAt)
        {
            return;
        }
        tokens.push_back(token);
    }
}

void getTokens(std::string & source, TokenList & tokens, char delim, const std::string & stopAt)
{
    std::stringstream stream(source);
    getTokens(stream, tokens, delim, stopAt);
}