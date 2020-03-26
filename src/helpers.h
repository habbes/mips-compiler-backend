#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> TokenList;

inline std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
inline std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
inline std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

bool getNextToken(std::string & source, std::string & token, char delim = ' ');
bool getNextToken(std::istream & source, std::string & token, char delim = ' ');
void getTokens(std::stringstream & source, TokenList & tokens, char delim = ' ', const std::string & stopAt = "");
void getTokens(std::string & source, TokenList & tokens, char delim = ' ', const std::string & stopAt = "");