#include "cpu/cpu.h"
#include "parser/instruction_parser.h"
#include <fstream>
#include <ios>

int main()
{
  hw::InstructionParser parser;
  std::ifstream str("../app/app.s", std::ios_base::in);
  auto res = hw::Binary(parser.parse(str));
  hw::CPU cpu;
  cpu.execute(res);
}