#pragma once

#include <memory>
#include "ir_program.h"

class IrParser
{
    std::istream & source_;
    std::unique_ptr<IrProgram> program_;

    void parseStatement(std::string & statement);
    bool parseFunction();
    bool parseFunctionSignature();
    bool parseIntList();
    bool parseFloatList();
    bool parseVarList(const std::string & dataType);
    bool parseFunctionBody();
    /**
     * reads the next statement from the source
     * @param nextStatement string where the read statement should be stored
     * @return whether the statement was read. False could indicate that the end of stream
     * was reached before finding a statement to read. Always ensure that true is returned
     * before using the value in nextStatement
     */
    bool readNextStatement(std::string & nextStatement);
public:
    IrParser(std::istream & source);
    void parse();
    IrProgram &program() const;
};
