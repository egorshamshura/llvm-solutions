#include "cpu.h"
#include "lib/sim.h"

void hw::CPU::execute(hw::Binary& bin) 
{
  m_bin = std::move(bin);
  simInit();
  while (m_run) 
  {
    m_bin.m_nextPC = m_bin.m_PC + 1;
    m_bin.instructions[m_bin.m_PC]->execute(*this);
    m_bin.m_PC = m_bin.m_nextPC;
  }
  simExit();
}