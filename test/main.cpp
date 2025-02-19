#include "cpu/cpu.h"
#include "cpu/ir_gen.h"
#include "parser/instruction_parser.h"
#include <fstream>
#include <ios>
#include "llvm/ExecutionEngine/MCJIT.h"
#include <iostream>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: path/to/app/file" << std::endl;
  }
  hw::InstructionParser parser;
  std::ifstream str(argv[1], std::ios_base::in);
  auto res = hw::Binary(parser.parse(str));
  hw::CPU cpu;
  hw::IRGen gen;
  gen.build(res);
  gen.execute(cpu);
  // cpu.execute(res);
}
