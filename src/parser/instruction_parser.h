#pragma once

#include <fstream>

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