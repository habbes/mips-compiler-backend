#include <fstream>
#include "ir_parser.h"

#define test_expect(expr, message, ...) if(!(expr)) {fprintf(stderr, "Test failed: ");fprintf(stderr, (message), __VA_ARGS__); fprintf(stderr,"\n"); return false;}
#define test_run_scenario(fn) if(!(fn())) {fprintf(stderr, "\nTESTS FAILED\n"); return EXIT_FAILURE;}

bool testSimpleParser()
{
    std::string filename = "../test_cases/examples/ir/sum-to-n.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();
    
    auto & func = program[0];
    test_expect(func.name() == "main", "Expected func 'main' but found '%s'", func.name().c_str());
    test_expect(func.returnType().name == "void", "Expected void return type but found '%s'", func.returnType().name.c_str());
    test_expect(func.params().size() == 0, "Expected 0 params but found %lu", func.params().size());
    return true;
}

bool testMultiFunction()
{
    std::string filename = "../test_cases/examples/ir/function.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();

    test_expect(program.numFunctions() == 5, "Expected 5 functions but got %d", program.numFunctions());
    
    auto & subtractInt = program[0];

    test_expect(subtractInt.name() == "subtractInt", "subtractInt name subtractInt but got %s", subtractInt.name().c_str());
    test_expect(subtractInt.returnType().name == "int", "subtractInt should return int subtractInt but got %s", subtractInt.returnType().name.c_str());
    test_expect(subtractInt.params().size(), "subtractInt should have 2 params but got %lu", subtractInt.params().size());
    test_expect(subtractInt.params()[0].dataType == "int", "subtractInt param 0 should be int but got %s", subtractInt.params()[0].dataType.c_str());
    test_expect(subtractInt.params()[0].name == "first_s2", "subtractInt param 0 should first_s2 but got %s", subtractInt.params()[0].name.c_str());
    test_expect(subtractInt.params()[1].dataType == "int", "subtractInt param 0 should be int but got %s", subtractInt.params()[1].dataType.c_str());
    test_expect(subtractInt.params()[1].name == "second_s2", "subtractInt param 0 should first_s2 but got %s", subtractInt.params()[1].name.c_str());
  
    auto & isFive = program[3];
    test_expect(isFive.name() == "isFive", "expected func isFive but got %s", isFive.name().c_str());
    test_expect(isFive.returnType().name == "int", "isFive should return int but got %s", isFive.returnType().name.c_str());
    test_expect(isFive.params().size() == 1, "isFive should have 1 param but got %lu", isFive.params().size());
    test_expect(isFive.params()[0].dataType == "int", "isFive param 0 should be int but got %s", isFive.params()[0].dataType.c_str());
    test_expect(isFive.params()[0].dataType == "number_s5", "isFive params 0 should be number_s5 but got %s", isFive.params()[0].name.c_str());
    return true;
}



int main(int argc, char *argv[])
{
    test_run_scenario(testSimpleParser);
    test_run_scenario(testMultiFunction);

    puts("SUCCESS!");
    return 0;
}