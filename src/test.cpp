#include <fstream>
#include "ir_parser.h"
#include "ir2mips.h"
#include "cfg.h"
#include "naive_reg_allocator.h"
#include "briggs_function_reg_allocator.h"
#include "interference_graph.h"

#define test(expr, message) if (!(expr)) { fprintf(stderr, "Test failed: %s", (message)); return false; }
#define test_expect(expr, message, ...) if(!(expr)) {fprintf(stderr, "Test failed: ");fprintf(stderr, (message), __VA_ARGS__); fprintf(stderr,"\n"); return false;}
#define test_run_scenario(fn) if(!(fn())) {fprintf(stderr, "\nTESTS FAILED\n"); return EXIT_FAILURE;}

#define test_objects_equal(actual, expected) test_expect((actual) == (expected), "expected %s but got %s", (expected).toString().c_str(), (actual).toString().c_str())
#define test_strings_equal(actual, expected) test_expect((actual) == (expected), "expected %s but got %s", (expected), (actual).c_str())
#define object_cstr(o) (o).toString().c_str()

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

bool testParseArray()
{
    std::string filename = "../test_cases/examples/ir/array.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & program = parser.program();

    auto & func = program[0];

    SymbolInfo goblins_s1 = { .name = "goblins_s1", .type = SymbolType::VAR, .dataType = DTYPE_INT, 0, 0, .isArray = true, .arraySize = 5 };
    test_expect(func.vars().at("goblins_s1") == goblins_s1, "goblins_s1 should be int array of size 5, but got %s",
        func.vars().at("goblins_s1").toString().c_str());
    
    IrInstruction ins0 = {
        .op = OpCode::ASSIGN,
        .params = {
            goblins_s1,
            { .name = "5", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 5 },
            { .name = "16", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 16 }
        }
    };
    test_expect(func.instruction(0) == ins0, "instruction 0 should be assign,goblins_s1,5,16 but got %s",
        func.instruction(0).toString().c_str());
    
    IrInstruction ins2 = {
        .op = OpCode::ARRAY_STORE,
        .params = {
            goblins_s1,
            { .name = "3", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 3 },
            { .name = "11", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 11 }
        }
    };
    test_expect(func.instruction(2) == ins2, "instruction 2 should be array_store,goblins_s1,3,11 but got %s",
        func.instruction(2).toString().c_str());

    IrInstruction ins4 = {
        .op = OpCode::ARRAY_LOAD,
        .params = {
            { .name = "_t1_s0", .type = SymbolType::VAR, .dataType = DTYPE_INT },
            goblins_s1,
            { .name = "3", .type = SymbolType::CONST, .dataType = DTYPE_INT, .intValue = 3 }
        }
    };
    test_expect(func.instruction(4) == ins4, "instruction 4 should be array_load,_t1_s0,goblins_s1,3 but got %s",
        func.instruction(4).toString().c_str());
     
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

#define test_mips_instruction(inst, expected) test_expect((inst) == (expected), "expected mips instruction '%s' but got '%s'", (expected), (inst).toString().c_str())

bool testSimpleMipsTranslation()
{
    std::string filename = "../test_cases/examples/ir/sum-to-n.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    NaiveRegAllocator allocator;
    Ir2Mips translator(irProgram, allocator);
    translator.translate();
    auto & mipsProgram = translator.mips();

    // built-in funcs
    test_strings_equal(mipsProgram[0].name(), "__main__");
    test_strings_equal(mipsProgram[2].name(), "printi");
    test_strings_equal(mipsProgram[3].name(), "storeIntArray");
    test_strings_equal(mipsProgram[4].name(), "loadIntArray");
    test_strings_equal(mipsProgram[5].name(), "exit");

    auto & func = mipsProgram[1];
    test_expect(func.name() == "main", "expected main but got %s", func.name().c_str());

    using mips::MipsSymbol;
    MipsSymbol total_s1 = { .name = "total_s1", .type = mips::VAR, mips::WORD };
    MipsSymbol n_s1 = { "n_s1", mips::VAR, mips::WORD };
    MipsSymbol index_s1 = { "index_s1", mips::VAR, mips::WORD };
    MipsSymbol _t1_s0 = { "_t1_s0", mips::VAR, mips::WORD };
    MipsSymbol _t2_s0 = { "_t2_s0", mips::VAR, mips::WORD };
    MipsSymbol _t3_s0 = { "_t3_s0", mips::VAR, mips::WORD };
    MipsSymbol _t4_s0 = { "_t4_s0", mips::VAR, mips::WORD };
    auto vars = func.vars();
    test_expect(vars.at("total_s1") == total_s1, "expected total_s1 but got %s", vars.at("total_s1").toString().c_str());
    test_expect(vars.at("n_s1") == n_s1, "expected n_s1 but got %s", vars.at("n_s1").toString().c_str());
    test_expect(vars.at("index_s1") == index_s1, "expected index_s1 but got %s", vars.at("index_s1").toString().c_str());
    test_expect(vars.at("_t1_s0") == _t1_s0, "expected _t1_s0 but got %s", vars.at("_t1_s0").toString().c_str());
    test_expect(vars.at("_t2_s0") == _t2_s0, "expected _t2_s0 but got %s", vars.at("_t2_s0").toString().c_str());
    test_expect(vars.at("_t3_s0") == _t3_s0, "expected _t3_s0 but got %s", vars.at("_t3_s0").toString().c_str());
    test_expect(vars.at("_t4_s0") == _t4_s0, "expected _t4_s0 but got %s", vars.at("_t4_s0").toString().c_str());

    auto initials = func.initialValues();
    test_expect(initials.at("total_s1") == "0", "expected total_s1 to be 0 but got %s", initials.at("total_s1").c_str());
    
    test_mips_instruction(func.instruction(0), "sw $ra, main_saved_ra_");
    test_mips_instruction(func.instruction(1), "li $t8, 10");
    test_mips_instruction(func.instruction(2), "sw $t8, n_s1");
    
    return true;
}

bool testMipsArithmeticAssignments()
{
    std::string filename = "../test_cases/examples/ir/very_simple.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    NaiveRegAllocator allocator;
    Ir2Mips translator(irProgram, allocator);
    translator.translate();
    auto & mipsProgram = translator.mips();

    auto & func = mipsProgram[1];

    // assign, n_s1, 10,
    test_mips_instruction(func.instruction(0), "li $t8, 10");
    test_mips_instruction(func.instruction(1), "sw $t8, n_s1");

    // main:
    test_mips_instruction(func.instruction(2), "main:")
    // assign, b_s1, n_s1,
    test_mips_instruction(func.instruction(3), "lw $t8, n_s1");
    test_mips_instruction(func.instruction(4), "sw $t8, b_s1");
    // add, n_s1, b_s1, res_s1
    test_mips_instruction(func.instruction(5), "lw $t8, n_s1");
    test_mips_instruction(func.instruction(6), "lw $t9, b_s1");
    test_mips_instruction(func.instruction(7), "add $t8, $t8, $t9");
    test_mips_instruction(func.instruction(8), "sw $t8, res_s1");
    // mul, b_s1, 20, res_s1
    test_mips_instruction(func.instruction(9), "lw $t8, b_s1");
    test_mips_instruction(func.instruction(10), "li $t9, 20");
    test_mips_instruction(func.instruction(11), "mul $t8, $t8, $t9");
    test_mips_instruction(func.instruction(12), "sw $t8, res_s1");
    // div, 100, b_s1, b_s1
    test_mips_instruction(func.instruction(13), "li $t8, 100");
    test_mips_instruction(func.instruction(14), "lw $t9, b_s1");
    test_mips_instruction(func.instruction(15), "div $t8, $t8, $t9");
    test_mips_instruction(func.instruction(16), "sw $t8, b_s1");
    // sub, 100, 20, res_s1
    test_mips_instruction(func.instruction(17), "li $t8, 100");
    test_mips_instruction(func.instruction(18), "li $t9, 20");
    test_mips_instruction(func.instruction(19), "sub $t8, $t8, $t9");
    test_mips_instruction(func.instruction(20), "sw $t8, res_s1");
    // return, , , 
    test_mips_instruction(func.instruction(21), "jr $ra");


    return true;
}

bool testCfgSimpleBasicBlocks()
{
    std::string filename = "../test_cases/examples/ir/simple_blocks.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    
    auto & func = irProgram[0];
    Cfg cfg(func);
    auto & blocks = cfg.blocks();
    test_expect(blocks.size() == 4, "expected 4 blocks but got %lu", blocks.size());
    BasicBlock block0 = { .id = 0, .first = 0, .last = 2};
    BasicBlock block1 = { 1, 3, 5 };
    BasicBlock block2 = { 2, 6, 8 };
    BasicBlock block3 = { 3, 9, 11 };
    test_objects_equal(blocks[0], block0);
    test_objects_equal(blocks[1], block1);
    test_objects_equal(blocks[2], block2);
    test_objects_equal(blocks[3], block3);

    auto & nodes = cfg.nodes();
    test_expect(nodes.size() == 4, "expected 4 nodes but got %lu", nodes.size());
    CfgNode node0 = { .block = 0, .successors = { 1 }, .predecessors = {} };
    CfgNode node1 = { 1, { 2, 3 }, { 0, 2 } };
    CfgNode node2 = { 2, { 1 }, { 1 } };
    CfgNode node3 = { 3, {}, { 1 } };
    test_objects_equal(nodes[0], node0);
    test_objects_equal(nodes[1], node1);
    test_objects_equal(nodes[2], node2);
    test_objects_equal(nodes[3], node3);

    return true;
}

template<class T>
bool testObjectsEqual(T actual, T expected)
{
    test_objects_equal(actual, expected);
    return true;
}

#define test_connected(graph, node1, node2) test_expect((graph).areConnected((node1), (node2)), "%s and %s should be connected", (node1), (node2))
#define test_not_connected(graph, node1, node2) test_expect(!(graph).areConnected((node1), (node2)), "%s and %s should not be connected", (node1), (node2))
#define test_node_cost(graph, nodeId, expectedCost) test_expect((graph).node((nodeId)).cost == expectedCost, \
    "node %s should have cost %d", (graph).node(nodeId).toString().c_str(), (expectedCost))

bool testBriggsAllocator()
{
    std::string filename = "../test_cases/examples/ir/sum-to-n.ir";
    std::ifstream source(filename);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    auto & func = irProgram[0];
    BriggsFunctionRegAllocator allocator(func);

    // Local in-block live ranges
    auto & blockRanges = allocator.blockLiveRanges();

    auto n = blockRanges.at("n_s1");
    auto nR0 = BlockLiveRange{ .block = 0, .start = 0, .end = 3, .definesVar = true };
    auto nR1 = BlockLiveRange{ 1, 4, 5 };
    auto nR2 = BlockLiveRange{ 2, 6, 9 };
    auto nR3 = BlockLiveRange{ 3, 10, 13 };
    test_objects_equal(n[0], nR0);
    test_objects_equal(n[1], nR1);
    test_objects_equal(n[2], nR2);
    test_objects_equal(n[3], nR3);

    auto total = blockRanges.at("total_s1");
    auto totalR0 = BlockLiveRange{ 0, 2, 3, true };
    auto totalR1 = BlockLiveRange{ 1, 4, 5 };
    auto totalR2 = BlockLiveRange{ 2, 6, 6 };
    auto totalR3 = BlockLiveRange{ 2, 7, 9, true };
    auto totalR4 = BlockLiveRange{ 3, 10, 11 };
    test_objects_equal(total[0], totalR0);
    test_objects_equal(total[1], totalR1);
    test_objects_equal(total[2], totalR2);
    test_objects_equal(total[3], totalR3);
    test_objects_equal(total[4], totalR4);

    auto index = blockRanges.at("index_s1");
    auto indexR0 = BlockLiveRange{ 0, 3, 3, true };
    auto indexR1 = BlockLiveRange{ 1, 4, 5 };
    auto indexR2 = BlockLiveRange{ 2, 6, 8 };
    auto indexR3 = BlockLiveRange{ 2, 8, 9, true };
    test_objects_equal(index[0], indexR0);
    test_objects_equal(index[1], indexR1);
    test_objects_equal(index[2], indexR2);
    test_objects_equal(index[3], indexR3);

    auto t1 = blockRanges.at("_t1_s0");
    auto t1R0 = BlockLiveRange{ 2, 6, 7, true };
    test_objects_equal(t1[0], t1R0);

    auto t2 = blockRanges.at("_t2_s0");
    auto t2R0 = BlockLiveRange{ 3, 12, 13, true };
    test_objects_equal(t2[0], t2R0);

    auto t3 = blockRanges.at("_t3_s0");
    auto t3R0 = BlockLiveRange{ 3, 13, 14, true };
    test_objects_equal(t3[0], t3R0);

    auto t4 = blockRanges.at("_t4_s0");
    auto t4R0 = BlockLiveRange{ 3, 14, 15, true };
    test_objects_equal(t4[0], t4R0);

    // Webs
    auto & webs = allocator.liveRanges();
    Web nWeb0 = { "n_s1", { nR0, nR1, nR2, nR3 } };
    test_expect(std::find(webs.begin(), webs.end(), nWeb0) != webs.end(), "did not find web %s", object_cstr(nWeb0));

    Web totalWeb0 = { "total_s1", { totalR0, totalR1, totalR2, totalR3, totalR4 } };
    test_expect(std::find(webs.begin(), webs.end(), totalWeb0) != webs.end(), "did not find web %s", object_cstr(totalWeb0));

    Web indexWeb0 = { "index_s1", { indexR0, indexR1, indexR2, indexR3 } };
    test_expect(std::find(webs.begin(), webs.end(), indexWeb0) != webs.end(), "did not find web %s", object_cstr(indexWeb0));

    Web t1Web0 = { "_t1_s0", { t1R0 } };
    test_expect(std::find(webs.begin(), webs.end(), t1Web0) != webs.end(), "did not find web %s", object_cstr(t1Web0));

    Web t2Web0 = { "_t2_s0", { t2R0 } };
    test_expect(std::find(webs.begin(), webs.end(), t2Web0) != webs.end(), "did not find web %s", object_cstr(t2Web0));
    
    Web t3Web0 = { "_t3_s0", { t3R0 } };
    test_expect(std::find(webs.begin(), webs.end(), t3Web0) != webs.end(), "did not find web %s", object_cstr(t3Web0));

    Web t4Web0 = { "_t4_s0", { t4R0 } };
    test_expect(std::find(webs.begin(), webs.end(), t4Web0) != webs.end(), "did not find web %s", object_cstr(t4Web0));

    test_expect(webs.size() == 7, "expected 7 webs but found %lu", webs.size());

    // Interference graph
    auto & graph = allocator.interferenceGraph();
    test_expect(graph.nodes().size() == 7, "expected 7 nodes in interference graph but got %lu", graph.nodes().size());
    
    test_connected(graph, nWeb0.id().c_str(), totalWeb0.id().c_str());
    test_connected(graph, nWeb0.id().c_str(), indexWeb0.id().c_str());
    test_connected(graph, nWeb0.id().c_str(), t1Web0.id().c_str());
    test_connected(graph, nWeb0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, nWeb0.id().c_str(), t3Web0.id().c_str());
    test_not_connected(graph, nWeb0.id().c_str(), t4Web0.id().c_str());

    test_connected(graph, totalWeb0.id().c_str(), nWeb0.id().c_str());
    test_connected(graph, totalWeb0.id().c_str(), indexWeb0.id().c_str());
    test_not_connected(graph, totalWeb0.id().c_str(), t1Web0.id().c_str());
    test_not_connected(graph, totalWeb0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, totalWeb0.id().c_str(), t3Web0.id().c_str());
    test_not_connected(graph, totalWeb0.id().c_str(), t4Web0.id().c_str());

    test_connected(graph, indexWeb0.id().c_str(), nWeb0.id().c_str());
    test_connected(graph, indexWeb0.id().c_str(), totalWeb0.id().c_str());
    test_connected(graph, indexWeb0.id().c_str(), t1Web0.id().c_str());
    test_not_connected(graph, indexWeb0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, indexWeb0.id().c_str(), t3Web0.id().c_str());
    test_not_connected(graph, indexWeb0.id().c_str(), t4Web0.id().c_str());

    test_connected(graph, t1Web0.id().c_str(), nWeb0.id().c_str());
    test_connected(graph, t1Web0.id().c_str(), indexWeb0.id().c_str());
    test_not_connected(graph, t1Web0.id().c_str(), totalWeb0.id().c_str());
    test_not_connected(graph, t1Web0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, t1Web0.id().c_str(), t3Web0.id().c_str());
    test_not_connected(graph, t1Web0.id().c_str(), t4Web0.id().c_str());

    test_connected(graph, t2Web0.id().c_str(), nWeb0.id().c_str());
    test_not_connected(graph, t2Web0.id().c_str(), indexWeb0.id().c_str());
    test_not_connected(graph, t2Web0.id().c_str(), totalWeb0.id().c_str());
    test_not_connected(graph, t2Web0.id().c_str(), t1Web0.id().c_str());
    test_not_connected(graph, t2Web0.id().c_str(), t3Web0.id().c_str());
    test_not_connected(graph, t2Web0.id().c_str(), t4Web0.id().c_str());

    test_not_connected(graph, t3Web0.id().c_str(), nWeb0.id().c_str());
    test_not_connected(graph, t3Web0.id().c_str(), indexWeb0.id().c_str());
    test_not_connected(graph, t3Web0.id().c_str(), totalWeb0.id().c_str());
    test_not_connected(graph, t3Web0.id().c_str(), t1Web0.id().c_str());
    test_not_connected(graph, t3Web0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, t3Web0.id().c_str(), t4Web0.id().c_str());

    test_not_connected(graph, t4Web0.id().c_str(), nWeb0.id().c_str());
    test_not_connected(graph, t4Web0.id().c_str(), indexWeb0.id().c_str());
    test_not_connected(graph, t4Web0.id().c_str(), totalWeb0.id().c_str());
    test_not_connected(graph, t4Web0.id().c_str(), t1Web0.id().c_str());
    test_not_connected(graph, t4Web0.id().c_str(), t2Web0.id().c_str());
    test_not_connected(graph, t4Web0.id().c_str(), t3Web0.id().c_str());

    // estimate spill costs
    test_node_cost(graph, nWeb0.id(), 13);
    test_node_cost(graph, totalWeb0.id(), 22);
    test_node_cost(graph, indexWeb0.id(), 41);
    test_node_cost(graph, t1Web0.id(), 20);
    test_node_cost(graph, t2Web0.id(), 2);
    test_node_cost(graph, t3Web0.id(), 2);
    test_node_cost(graph, t4Web0.id(), 2);


    return true;
}

bool testSimpleGraphColoring ()
{
    int numColors = 3;
    InterferenceGraph ig(numColors);
    ig.addNode("s0");
    ig.addNode("s1");
    ig.addNode("s2");
    ig.addNode("s3");
    ig.addNode("s4");

    ig.connectNodes("s0", "s1");
    ig.connectNodes("s0", "s2");
    ig.connectNodes("s0", "s3");
    ig.connectNodes("s1", "s2");
    ig.connectNodes("s1", "s3");
    ig.connectNodes("s2", "s4");
    ig.connectNodes("s3", "s4");

    ig.colorGraph();

    for (auto & item : ig.nodes())
    {
        auto & node = item.second;
        test_expect(node.hasColor(), "node %s should be colored", node.toString().c_str());
        test_expect(node.color < numColors, "node %s color should be between 0-k", node.toString().c_str());
        for (auto & neighbor : node.neighbors)
        {
            test_expect(node.color != ig.node(neighbor).color,
                "node %s should not have same color as neighbor %s",
                node.toString().c_str(), ig.node(neighbor).toString().c_str());
        }
    }

    return true;
}

bool testGraphColoringWithSpills()
{
    int numColors = 3;
    InterferenceGraph ig(numColors);
    ig.addNode("s0", 4);
    ig.addNode("s1", 2);
    ig.addNode("s2", 3);
    ig.addNode("s3", 4);
    ig.addNode("s4", 1);

    ig.connectNodes("s0", "s1");
    ig.connectNodes("s0", "s2");
    ig.connectNodes("s0", "s3");
    ig.connectNodes("s1", "s2");
    ig.connectNodes("s1", "s3");
    ig.connectNodes("s2", "s3");
    ig.connectNodes("s2", "s4");
    ig.connectNodes("s3", "s4");

    ig.colorGraph();

    // not all nodes can be colored in this graph
    // s1 should be spilled because it has the lowest spill cost
    // of all the nodes that have degree >= 3
    auto s2 = ig.node("s1");
    test_expect(!s2.hasColor(), "node %s should not have a color", s2.toString().c_str());

    // all other nodes should be colored
    for (auto & item : ig.nodes())
    {
        if (item.first == "s1") continue;

        auto & node = item.second;
        test_expect(node.hasColor(), "node %s should be colored", node.toString().c_str());
        test_expect(node.color < numColors, "node %s color should be between 0-k", node.toString().c_str());
        for (auto & neighbor : node.neighbors)
        {
            test_expect(node.color != ig.node(neighbor).color,
                "node %s should not have same color as neighbor %s",
                node.toString().c_str(), ig.node(neighbor).toString().c_str());
        }
    }

    return true;
}


int main(int argc, char *argv[])
{
    test_run_scenario(testParseSimpleFunction);
    test_run_scenario(testParseMultipleFunctions);
    test_run_scenario(testFunctionMemoryBugs);
    test_run_scenario(testParseArray);
    test_run_scenario(testSimpleMipsTranslation);
    test_run_scenario(testMipsArithmeticAssignments);
    test_run_scenario(testCfgSimpleBasicBlocks);
    test_run_scenario(testBriggsAllocator);
    test_run_scenario(testSimpleGraphColoring);
    test_run_scenario(testGraphColoringWithSpills);

    puts("SUCCESS!");
    return 0;
}