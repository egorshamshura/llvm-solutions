#include "cpu/cpu.h"
#include "cpu/ir_gen.h"
#include "parser/instruction_parser.h"
#include <fstream>
#include <ios>

#include <iostream>

int main()
{
  hw::InstructionParser parser;
  std::ifstream str("../app/app2.s", std::ios_base::in);
  auto res = hw::Binary(parser.parse(str));
  hw::CPU cpu;
  cpu.execute(res);;
}