#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "instruction/instruction.h"

namespace hw 
{
namespace constant 
{
static constexpr uint32_t REG_SIZE = 16;
static constexpr uint32_t MEM_SIZE = 262144;
static constexpr uint32_t DIS_WIDTH = 256;
static constexpr uint32_t DIS_HEIGHT = 128;
static constexpr uint32_t DIS_SCALE = 4;
}; // namespace constants

struct Binary
{
  std::vector<std::shared_ptr<Instruction>> instructions;
  std::unordered_map<std::string, size_t> label2pc;
  uint32_t m_PC = 0;
  uint32_t m_nextPC = 1;
};

struct CPU
{
  void execute(Binary& bin);

  Binary m_bin;
  uint32_t m_regFile[constant::REG_SIZE] = {};
  uint32_t m_mem[constant::MEM_SIZE] = {};
  uint32_t m_run = 1;
  uint32_t m_mem_idx = 0;
};

}; // namespace hw