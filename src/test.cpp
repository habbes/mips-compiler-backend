#include <fstream>
#include "ir_parser.h"

bool testSimpleParser()
{
    std::string filename = "../test_cases/examples/ir/sum-to-n.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();
    
    auto & func = program[0];
    if (func.name() != "main")
    {
        puts("Wrong func name");
        return false;
    }

    if (func.returnType().name != "void")
    {
        printf("Incorrect return type %s\n", func.returnType().name.c_str());
        return false;
    }

    if (func.params().size() != 0)
    {
        printf("Incorrect params");
        return false;
    }
    return true;
}

bool testMultiFunction()
{
    std::string filename = "../test_cases/examples/ir/function.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();

    if (program.numFunctions() != 5)
    {
        puts("Incorrect num functions\n");
        return false;
    }
    
    auto & subtractInt = program[0];

    if (subtractInt.name() != "subtractInt")
    {
        return false;
    }
    if (subtractInt.returnType().name != "int")
    {
        return false;
    }
    if (subtractInt.params().size() != 2)
    {
        return false;
    }
    if (subtractInt.params()[0].dataType != "int")
    {
        return false;
    }
    if (subtractInt.params()[0].name != "first_s2")
    {
        return false;
    }
    if (subtractInt.params()[1].dataType != "int")
    {
        return false;
    }
    if (subtractInt.params()[1].name != "second_s2")
    {
        return false;
    }

    auto & isFive = program[3];
    if (isFive.name() != "isFive")
    {
        return false;
    }
    if (isFive.returnType().name != "int")
    {
        return false;
    }
    if (isFive.params().size() != 1)
    {
        return false;
    }
    if (isFive.params()[0].dataType != "int")
    {
        return false;
    }
    if (isFive.params()[0].name != "number_s5")
    {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!testSimpleParser())
    {
        puts("Tests failed");
        return 1;
    }

    if (!testMultiFunction())
    {
        puts("Tests failed");
        return 1;
    }

    puts("SUCCESS!");
    return 0;
}