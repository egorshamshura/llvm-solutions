#pragma once

#include "instruction/instruction.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace hw {
namespace constant {
static constexpr uint64_t REG_SIZE = 16;
static constexpr uint64_t MEM_SIZE = 262144;
static constexpr uint64_t DIS_WIDTH = 256;
static constexpr uint64_t DIS_HEIGHT = 128;
static constexpr uint64_t DIS_SCALE = 4;
}; // namespace constant

struct Binary {
  std::vector<std::shared_ptr<Instruction>> instructions;
  std::unordered_map<std::string, size_t> label2pc;
  uint64_t m_PC = 0;
  uint64_t m_nextPC = 1;
};

struct CPU {
  void execute(Binary& bin);

  void dump_regs() {
    for (int i = 0; i != constant::REG_SIZE; ++i) {
      std::cout << "x" << i << " = " << m_regFile[i] << "; ";
    }
    std::cout << std::endl;
  }

  Binary m_bin;
  uint64_t m_regFile[constant::REG_SIZE] = {};
  uint64_t m_mem[constant::MEM_SIZE] = {};
  uint64_t m_run = 1;
  uint64_t m_mem_idx = 0;
};

}; // namespace hw