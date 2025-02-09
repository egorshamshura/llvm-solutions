#pragma once

#include <vector>
#include <memory>
#include <fstream>

#include "instruction/instruction.h"
#include "cpu/cpu.h"

namespace hw
{

struct InstructionParser
{
  Binary parse(std::ifstream &input);
private:
  std::pair<std::string, std::unordered_map<std::string, size_t>> preprocess(std::ifstream &input);
};

} // namespace hw