# IR to MIPS Compiler Backend

This is a backend compiler. It compiles code from an intermediate-representation language
to MIPS assembly.

## How to build and run the project

### Building
The project root contains a script called run_build.sh that compiles and builds the project. Open the project root in a terminal and run:

```
$ ./run_build.sh
```

This will generate an executable called `ir2mips` and store it in the project root.
Note: the submission already include a pre-built `ir2mips` binary in the root, this will be replaced if you run the build script. There’s backup binary in the build directory in case there are issues building.

### Running the compiler

Run the compiler with the following command:
```
./ir2mips <source_file> <output_file> <allocator>
```
where:
- `source_file`: this is the path of the source IR file to compile
- `output_file`: this is the path where the generated MIPS file will be stored
- `allocator`: specifies which register allocator to use, options are naive, block and briggs

Example:
```
./ir2mips samples/ir/for-to.ir output/for-to-briggs.s briggs
```
## Source code overview
All of the source files for the compiler are located in the src file. Here are the main components of the compiler:
- **`IrProgram`** (`ir_program.h/cpp`, `ir_function.h/cpp`,  `ir_instruction.h/cpp`, `symbol_info.h/cpp`): This class represents an IR program, it contains objects representing all the functions, instructions and metadata in the IR program
- **`IrParser`** (`ir_parser.h/cpp`): This class parses IR code from a source text file and returns an IrProgram instance
- **`MipsProgram`** (`mips_program.h`, `mips_program.cpp`, `mips_function.h/cpp`, `mips_instruction.h/cpp`,  `mips_symbol.h/cpp`): This represents a MIPS program. It contains
`BaseRegAllocator` and `BaseFunctionRegAllocator` (`base_reg_allocator.h`, `base_function_reg_allocator.h`): These are interfaces that describe the common API that register allocators should implement
- **`Ir2Mips`** (`ir2mips.h/cpp`): This is the actual compiler, it takes an `IrProgram` and register allocator as input and returns a `MipsProgram` after compilation. When translating a variable symbol from ir to mips in an instruction, the compiler asks the allocator whether there’s a register allocated to that variable at that instruction (using the `allocator.getRegIfAllocated()` method). If the allocator returns a register, that register is used in the instruction, otherwise the compiler uses temporary registers in the instructions and adds instructions to load/store the variable (spill). The compiler also calls the allocator before and after each instruction, this allows the intra-block allocator to inject loads and stores at the beginning and end of each block.
- **`Cfg`** (`cfg.h/cpp`, `cfg_node.h/cpp`, `basic_block.h/cpp`): This implements a control flow graph. Given an `IrFunction`, it can detect all the basic blocks and their edges.
- **`InterferenceGraph`** (`interference_graph.h/cpp`): This represents an interference graph between live range webs. It implements the Briggs optimistic graph coloring algorithm.
- **`NaiveRegAllocator`** (`naive_reg_allocator.h`): Implements a naive register allocator that does not allocate registers, which results in spills for all variables
- **`BlockRegAllocator`** (`block_reg_allocator.h`, `block_function_reg_allocator.h/cpp`): implements the greedy intra-block register allocator
- **`BriggsRegAllocator`** (`briggs_reg_allocator.h`, `briggs_function_reg_allocator.h/cpp`, `live_range_web.h`): implements the briggs function-wide register allocator
- **`main.cpp`**: program entry point, runs the compiler
- **`test.cpp`**: unit tests

The project root contains the following scripts:
- **`run_build.sh`**: builds the project
- **`run_clean.sh`**: cleans artifacts generated from building the project
- **`run_unit_tests.sh`**: builds and runs unit tests in `src/test.cpp`
- **`run_quickcheck.sh`**: compiles and execute some test programs using a specific allocator (e.g. `./run_quickcheck.sh briggs`)
- **`run_e2e_tests.sh`**: compiles and executes some test cases and diffs the output with reference snapshots
- **`generate_samples.sh`**: compiles and execute the test programs used in this submission, store in the samples directory


## Sample output

All the sample output compiled assembly files are stored in the `samples/asm` directory. Each file is named using the pattern `<test-name>-<allocator>.s` from example `samples/asm/for-to-briggs.s`, `samples/asm/for-to-block.s`, `samples/asm/for-to-naive.s`.

In addition, the output generated from executing these samples in spim are stored in the `samples/res` directory with a similar naming pattern, but using the `.txt` extension. Example `samples/res/for-to-briggs.txt`, `samples/res/for-to-block.txt`, `samples/res/for-to-naive.txt`.


[Here's an example of liveness analysis and register allocation](./register_allocation_analysis.pdf)