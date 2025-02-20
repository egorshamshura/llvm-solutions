#pragma once

#include "cpu/cpu.h"

#include <fstream>

namespace hw {

struct InstructionParser {
  Binary parse(std::ifstream& input);

private:
  std::pair<std::string, std::unordered_map<std::string, size_t>> preprocess(std::ifstream& input);
};

} // namespace hw