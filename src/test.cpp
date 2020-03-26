#include <fstream>
#include "ir_parser.h"

#define test_expect(expr, message, ...) if(!(expr)) {fprintf(stderr, "Test failed: ");fprintf(stderr, (message), __VA_ARGS__); fprintf(stderr,"\n"); return false;}
#define test_run_scenario(fn) if(!(fn())) {fprintf(stderr, "\nTESTS FAILED\n"); return EXIT_FAILURE;}

bool testSimpleParser()
{
    std::string filename = "../test_cases/examples/ir/simple_test.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();
    
    auto & func = program[0];
    test_expect(func.name() == "main", "Expected func 'main' but found '%s'", func.name().c_str());
    test_expect(func.returnType().name == "void", "Expected void return type but found '%s'", func.returnType().name.c_str());
    test_expect(func.params().size() == 0, "Expected 0 params but found %lu", func.params().size());
    test_expect(func.vars().size() == 9, "func should have 9 vars but got %lu", func.vars().size());

    SymbolInfo total_s1 = { .name = "total_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo n_s1 = { .name = "n_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo index_s1 = { .name = "index_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo _t1_s0 = { .name = "_t1_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo _t2_s0 = { .name = "_t2_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo _t3_s0 = { .name = "_t3_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo _t4_s0 = { .name = "_t4_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT };
    SymbolInfo dummy_s0 = { .name = "dummy_s0", .type = SymbolType::VAR, .dataType = DTYPE_FLOAT };
    SymbolInfo dummy_float = { .name = "dummy_float", .type = SymbolType::VAR, .dataType = DTYPE_FLOAT };

    test_expect(func.vars().at("total_s1") == total_s1, "expected total_s1 but got %s", total_s1.toString().c_str());
    test_expect(func.vars().at("n_s1") == n_s1, "expected n_s1 but got %s", n_s1.toString().c_str());
    test_expect(func.vars().at("index_s1") == index_s1, "expected index_s1 but got %s", index_s1.toString().c_str());
    test_expect(func.vars().at("_t1_s0") == _t1_s0, "expected _t1_s0 but got %s", _t1_s0.toString().c_str());
    test_expect(func.vars().at("_t2_s0") == _t2_s0, "expected _t2_s0 but got %s", _t2_s0.toString().c_str());
    test_expect(func.vars().at("_t3_s0") == _t3_s0, "expected _t3_s0 but got %s", _t3_s0.toString().c_str());
    test_expect(func.vars().at("_t4_s0") == _t4_s0, "expected _t4_s0 but got %s", _t4_s0.toString().c_str());
    test_expect(func.vars().at("dummy_s0") == dummy_s0, "expected dummy_s0 but got %s", dummy_s0.toString().c_str());
    test_expect(func.vars().at("dummy_float") == dummy_float, "expected dummy_float but got %s", dummy_float.toString().c_str());

    test_expect(func.numInstructions() == 17, "func should have 17 instructions but got %d", func.numInstructions());

    IrInstruction ins1 = { 
        .op = OpCode::ASSIGN,
        .params = {
            { .name = "n_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "10", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 10 }
        }
    };

    test_expect(func.instruction(0) == ins1, "expect instruction 0 to be assign but got %s", func.instruction(0).toString().c_str());
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

    auto & addInt = program[1];
    test_expect(addInt.name() == "addInt", "expected func addInt but got %s", addInt.name().c_str());

    auto & multiplyInt = program[2];
    test_expect(multiplyInt.name() == "multiply", "expected func multiply but got %s", multiplyInt.name().c_str());
  
    auto & isFive = program[3];
    test_expect(isFive.name() == "isFive", "expected func isFive but got %s", isFive.name().c_str());
    test_expect(isFive.returnType().name == "int", "isFive should return int but got %s", isFive.returnType().name.c_str());
    test_expect(isFive.params().size() == 1, "isFive should have 1 param but got %lu", isFive.params().size());
    test_expect(isFive.params()[0].dataType == "int", "isFive param 0 should be int but got %s", isFive.params()[0].dataType.c_str());
    test_expect(isFive.params()[0].name == "number_s5", "isFive params 0 should be number_s5 but got %s", isFive.params()[0].name.c_str());

    auto & mainFunc = program[4];
    test_expect(mainFunc.name() == "main", "expect func main but got %s", mainFunc.name().c_str());
    test_expect(mainFunc.params().size() == 0, "main should have 0 params but got %lu", mainFunc.params().size());
    test_expect(mainFunc.returnType().name == "void", "main should return void but got %s", mainFunc.returnType().name.c_str());

    return true;
}



int main(int argc, char *argv[])
{
    test_run_scenario(testSimpleParser);
    // test_run_scenario(testMultiFunction);

    puts("SUCCESS!");
    return 0;
}