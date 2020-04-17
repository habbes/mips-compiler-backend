#include <iostream>
#include <fstream>
#include <sstream>
#include "ir_parser.h"
#include "ir2mips.h"
#include "naive_reg_allocator.h"

void printHelp()
{
    std::cout << "USAGE: ir2mips <input_file> <output_file>"
        << std::endl;
}

int main (int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "ERROR: Insuffcient parameters" << std::endl;
        printHelp();
        return EXIT_FAILURE;
    }

    std::string sourcePath = argv[1];
    std::string outPath = argv[2];

    std::ifstream source(sourcePath);
    if (source.fail())
    {
        std::cerr << "Failed to open file " << sourcePath << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream output(outPath);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    NaiveRegAllocator allocator;
    Ir2Mips compiler(irProgram, allocator);
    compiler.translate();
    auto & mipsProgram = compiler.mips();

    mipsProgram.write(output);

    std::cout << "Output compiled to " << outPath << std::endl;

    return 0;
}