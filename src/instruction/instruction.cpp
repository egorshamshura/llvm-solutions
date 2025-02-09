#include "instruction.h"
#include "lib/sim.h"
#include "cpu/cpu.h"

void hw::ADDInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] + cpu.m_regFile[_r3];
}

hw::Instr_t hw::ADDInstr::instr()
{
  return hw::Instr_t::ADD;
}

// void hw::ADDInstr::build_ir(IRBuilder<>& builder, uint32_t PC)
// {
  
// }

void hw::SUBInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] - cpu.m_regFile[_r3];
}

hw::Instr_t hw::SUBInstr::instr()
{
  return hw::Instr_t::SUB;
}

void hw::MULInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] * cpu.m_regFile[_r3];
}

hw::Instr_t hw::MULInstr::instr()
{
  return hw::Instr_t::MUL;
}

void hw::DIVInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] / cpu.m_regFile[_r3];
}

hw::Instr_t hw::DIVInstr::instr()
{
  return hw::Instr_t::DIV;
}

void hw::REMInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] % cpu.m_regFile[_r3];
}

hw::Instr_t hw::REMInstr::instr()
{
  return hw::Instr_t::REM;
}

void hw::XORInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] ^ cpu.m_regFile[_r3];
}

hw::Instr_t hw::XORInstr::instr()
{
  return hw::Instr_t::XOR;
}

void hw::INC_NEiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = static_cast<uint32_t>(++cpu.m_regFile[_r2] != _r3);
}

hw::Instr_t hw::INC_NEiInstr::instr()
{
  return hw::Instr_t::INC_NEi;
}

void hw::SUBiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] - _r3;
}

hw::Instr_t hw::SUBiInstr::instr()
{
  return hw::Instr_t::SUBi;
}

void hw::BR_CONDInstr::execute(CPU& cpu)
{
  if (cpu.m_regFile[_r1]) {
    cpu.m_bin.m_nextPC = _r2;
  }
}

hw::Instr_t hw::BR_CONDInstr::instr()
{
  return hw::Instr_t::BR_COND;
}

void hw::PUT_PIXELInstr::execute(CPU& cpu)
{
  simPutPixel(cpu.m_regFile[_r1], cpu.m_regFile[_r2], cpu.m_regFile[_r3]); 
}

hw::Instr_t hw::PUT_PIXELInstr::instr()
{
  return hw::Instr_t::PUT_PIXEL;
}

void hw::FLUSHInstr::execute(CPU& cpu)
{
  simFlush();
}

hw::Instr_t hw::FLUSHInstr::instr()
{
  return hw::Instr_t::FLUSH;
}

void hw::EXITInstr::execute(CPU& cpu)
{
  cpu.m_run = 0;
}

hw::Instr_t hw::EXITInstr::instr()
{
  return hw::Instr_t::EXIT;
}

