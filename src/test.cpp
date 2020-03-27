#include <fstream>
#include "ir_parser.h"

#define test_expect(expr, message, ...) if(!(expr)) {fprintf(stderr, "Test failed: ");fprintf(stderr, (message), __VA_ARGS__); fprintf(stderr,"\n"); return false;}
#define test_run_scenario(fn) if(!(fn())) {fprintf(stderr, "\nTESTS FAILED\n"); return EXIT_FAILURE;}

bool testParseSimpleFunction()
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

    IrInstruction ins0 = { 
        .op = OpCode::ASSIGN,
        .params = {
            { .name = "n_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "10", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 10 }
        }
    };
    test_expect(func.instruction(0) == ins0, "expect instruction 0 to be assign but got %s", func.instruction(0).toString().c_str());

    IrInstruction ins1 = {
        .op = OpCode::LABEL,
        .params = {
            { .name = "main", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(func.instruction(1) == ins1, "expect instruction 1 to be main: but got %s", func.instruction(1).toString().c_str());

    IrInstruction ins5 = {
        .op = OpCode::BRGT,
        .params = {
            { .name = "index_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "n_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "loop_label_1", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(func.instruction(5) == ins5, "instruction 5 should be brgt,index_s1,n_s1,loop_label but got %s", func.instruction(5).toString().c_str());

    IrInstruction ins6 = {
        .op = OpCode::ADD,
        .params = {
            { .name = "total_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "index_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "_t1_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(func.instruction(6) == ins6, "instruction 6 should be add,total_s1,index_s1,_t1_s0 but got %s", func.instruction(6).toString().c_str());

    IrInstruction ins9 = {
        .op = OpCode::GOTO,
        .params = {
            { .name = "loop_label_0", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(func.instruction(9) == ins9, "instruction 9 should be goto,loop_label_0 but got %s", func.instruction(9).toString().c_str());

    IrInstruction ins10 = {
        .op = OpCode::LABEL,
        .params = {
            { .name = "loop_label_1", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(func.instruction(10) == ins10, "instruction 10 should be loop_label_1: but got %s", func.instruction(10).toString().c_str());

    IrInstruction ins11 = {
        .op = OpCode::CALL,
        .params = {
            { .name = "printi", .type = SymbolType::FUNC },
            { .name = "total_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(func.instruction(11) == ins11, "instruction 11 to be call,printi,total_s1 but got %s", func.instruction(11).toString().c_str());

    IrInstruction ins13 = {
        .op = OpCode::MULT,
        .params = {
            { .name = "n_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "_t2_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "_t3_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(func.instruction(13) == ins13, "instruction 13 should be mul,n_s1,_t2_s0,_t3_s0 but got %s", func.instruction(14).toString().c_str());

    IrInstruction ins14 = {
        .op = OpCode::DIV,
        .params = {
            { .name = "_t3_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "2", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 2 },
            { .name = "_t4_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(func.instruction(14) == ins14, "instruction 14 should be div,_t3_s0,2,_t4_s0 but got %s", func.instruction(14).toString().c_str());

    IrInstruction ins16 = {
        .op = OpCode::RETURN
    };
    test_expect(func.instruction(16) == ins16, "instruction 16 should be return but got %s", func.instruction(16).toString().c_str());

    return true;
}

bool testParseMultipleFunctions()
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
    test_expect(subtractInt.params()[1].dataType == "int", "subtractInt param 1 should be int but got %s", subtractInt.params()[1].dataType.c_str());
    test_expect(subtractInt.params()[1].name == "second_s2", "subtractInt param 1 should first_s2 but got %s", subtractInt.params()[1].name.c_str());

    IrInstruction subIns0 = {
        .op = OpCode::SUB,
        .params = {
            { .name = "first_s2", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "second_s2", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "_t1_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(subtractInt.instruction(0) == subIns0, "subtractInt instruction 0 should be sub,first_s2,second_s2,_t1_s0 but got %s",
        subtractInt.instruction(0).toString().c_str());

    IrInstruction subIns1 = {
        .op = OpCode::RETURN,
        .params = {
            { .name = "_t1_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(subtractInt.instruction(1) == subIns1, "subtractInt instruction 1 should be return,_t1_s0 but got %s",
        subtractInt.instruction(1).toString().c_str());

    auto & addInt = program[1];
    test_expect(addInt.name() == "addInt", "expected func addInt but got %s", addInt.name().c_str());

    auto & multiplyInt = program[2];
    test_expect(multiplyInt.name() == "multiply", "expected func multiply but got %s", multiplyInt.name().c_str());

    IrInstruction mulInst2 = {
        .op = OpCode::BRGT,
        .params = {
            { .name = "a_s4", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "5", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 5 },
            { .name = "loop_label_1", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(multiplyInt.instruction(2) == mulInst2, "multiplyInt instruction 2 should be brgt but got %s",
        multiplyInt.instruction(2).toString().c_str());
  
    auto & isFive = program[3];
    test_expect(isFive.name() == "isFive", "expected func isFive but got %s", isFive.name().c_str());
    test_expect(isFive.returnType().name == "int", "isFive should return int but got %s", isFive.returnType().name.c_str());
    test_expect(isFive.params().size() == 1, "isFive should have 1 param but got %lu", isFive.params().size());
    test_expect(isFive.params()[0].dataType == "int", "isFive param 0 should be int but got %s", isFive.params()[0].dataType.c_str());
    test_expect(isFive.params()[0].name == "number_s5", "isFive params 0 should be number_s5 but got %s", isFive.params()[0].name.c_str());

    IrInstruction fiveIns1 = {
        .op = OpCode::BRNEQ,
        .params = {
            { .name = "number_s5", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "5", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 5 },
            { .name = "if_label_2", .type = SymbolType::TARGET_LABEL }
        }
    };
    test_expect(isFive.instruction(1) == fiveIns1, "isFive instruction 1 should be brneq but got %s",
        isFive.instruction(1).toString().c_str());

    auto & mainFunc = program[4];
    test_expect(mainFunc.name() == "main", "expect func main but got %s", mainFunc.name().c_str());
    test_expect(mainFunc.params().size() == 0, "main should have 0 params but got %lu", mainFunc.params().size());
    test_expect(mainFunc.returnType().name == "void", "main should return void but got %s", mainFunc.returnType().name.c_str());

    IrInstruction mainIns1 = {
        .op = OpCode::CALLR,
        .params = {
            { .name = "_t5_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "subtractInt", .type = SymbolType::FUNC },
            { .name = "4", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 4 },
            { .name = "3", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 3 }
        }
    };
    test_expect(mainFunc.instruction(1) == mainIns1, "main instruction 1 should be callr,_t5_s0,subtractInt,4,3 but got %s",
        mainFunc.instruction(1).toString().c_str());
    
    IrInstruction mainIns26 = {
        .op = OpCode::CALLR,
        .params = {
            { .name = "_t11_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "addInt", .type = SymbolType::FUNC },
            { .name = "one_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            { .name = "two_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT }
        }
    };
    test_expect(mainFunc.instruction(1) == mainIns1, "main instruction 1 should be callr,_t11_s0,addInt,one_s1,two_s1 but got %s",
        mainFunc.instruction(1).toString().c_str());

    return true;
}

bool testFunctionMemoryBugs()
{
    // std::string filename = "../test_cases/examples/ir/simple_test.ir";
    // std::ifstream source(filename);

    // IrParser parser(source);
    // parser.parse();
    // auto & program = parser.program();

    IrProgram program;
    auto & func = program.newFunction("func");
    test_expect(func.name() == "func", "incorrect func name %s", func.name().c_str());
    // auto & func = program[0];

    IrInstruction inst = { .op = OpCode::ASSIGN };
    func.addInstruction(std::make_unique<IrInstruction>(inst));
    auto inst1 = func.instruction(0);
    test_expect(inst1.op == OpCode::ASSIGN, "expected inst to be %s", inst1.toString().c_str());
    auto & inst2 = func.instruction(0);
    test_expect(inst2.op == OpCode::ASSIGN, "expected inst to be %s", inst2.toString().c_str());

    return true;
}


int main(int argc, char *argv[])
{
    test_run_scenario(testParseSimpleFunction);
    test_run_scenario(testParseMultipleFunctions);
    test_run_scenario(testFunctionMemoryBugs);

    puts("SUCCESS!");
    return 0;
}