#include "cpu/cpu.h"
#include "cpu/ir_gen.h"
#include "parser/instruction_parser.h"
#include <fstream>
#include <ios>
#include "llvm/ExecutionEngine/MCJIT.h"
#include <iostream>

int main()
{
  hw::InstructionParser parser;
  std::ifstream str("../test/test_apps/t1_alloc_writei.s", std::ios_base::in);
  auto res = hw::Binary(parser.parse(str));
  hw::CPU cpu;
  hw::IRGen gen;
  gen.build(res);
  gen.execute(cpu);
  // cpu.execute(res);
}
