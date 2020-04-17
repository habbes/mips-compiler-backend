#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "ir_parser.h"
#include "ir2mips.h"
#include "naive_reg_allocator.h"
#include "block_reg_allocator.h"

void printHelp()
{
    std::cout
        << "USAGE: ir2mips <input_file> <output_file> [<reg_allocator>]" << std::endl
        << "reg_allocator is one of: naive|block|briggs"
        << std::endl;
}

int main (int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "ERROR: Insuffcient parameters" << std::endl;
        printHelp();
        return EXIT_FAILURE;
    }

    std::string sourcePath = argv[1];
    std::string outPath = argv[2];
    std::string allocatorName = argv[3];

    std::ifstream source(sourcePath);
    if (source.fail())
    {
        std::cerr << "Failed to open file " << sourcePath << std::endl;
        return EXIT_FAILURE;
    }

    std::unique_ptr<BaseRegAllocator> allocator;
    if (allocatorName == "naive")
    {
        allocator = std::move(std::make_unique<NaiveRegAllocator>());
    }
    else if (allocatorName == "block")
    {
        allocator = std::move(std::make_unique<BlockRegAllocator>());
    }
    else
    {
        std::cerr << "Unknown register allocator: " << allocatorName << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream output(outPath);

    IrParser parser(source);
    parser.parse();
    auto & irProgram = parser.program();
    
    Ir2Mips compiler(irProgram, *allocator);
    compiler.translate();
    auto & mipsProgram = compiler.mips();

    mipsProgram.write(output);

    std::cout << "Output compiled to " << outPath << std::endl;

    return 0;
}