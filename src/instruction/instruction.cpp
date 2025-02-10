#include "instruction.h"
#include "lib/sim.h"
#include "cpu/cpu.h"
#include <llvm-18/llvm/Support/raw_ostream.h>

extern bool ___temp;

namespace
{

Value* GEP2_32(uint32_t arg, GlobalVariable *regFile, IRBuilder<> &builder) 
{
  ArrayType *regFileType = ArrayType::get(Type::getInt32Ty(builder.getContext()), hw::constant::REG_SIZE);
  return builder.CreateConstGEP2_32(regFileType, regFile, 0, arg);
}

LoadInst* load(uint32_t arg, GlobalVariable *regFile, IRBuilder<> &builder)
{
  return builder.CreateLoad(Type::getInt32Ty(builder.getContext()), GEP2_32(arg, regFile, builder));
}
} // anonymous namespace

void hw::ADDInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] + cpu.m_regFile[_r3];
}

hw::Instr_t hw::ADDInstr::instr()
{
  return hw::Instr_t::ADD;
}

void hw::ADDInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateAdd(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::SUBInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] - cpu.m_regFile[_r3];
}

hw::Instr_t hw::SUBInstr::instr()
{
  return hw::Instr_t::SUB;
}

void hw::SUBInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateSub(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::MULInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] * cpu.m_regFile[_r3];
}

hw::Instr_t hw::MULInstr::instr()
{
  return hw::Instr_t::MUL;
}

void hw::MULInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateMul(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::DIVInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] / cpu.m_regFile[_r3];
}

hw::Instr_t hw::DIVInstr::instr()
{
  return hw::Instr_t::DIV;
}

void hw::DIVInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateSDiv(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::REMInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] % cpu.m_regFile[_r3];
}

hw::Instr_t hw::REMInstr::instr()
{
  return hw::Instr_t::REM;
}

void hw::REMInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateSRem(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::XORInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] ^ cpu.m_regFile[_r3];
}

hw::Instr_t hw::XORInstr::instr()
{
  return hw::Instr_t::XOR;
}

void hw::XORInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateXor(load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::INC_NEiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = static_cast<uint32_t>(++cpu.m_regFile[_r2] != _r3);
}

hw::Instr_t hw::INC_NEiInstr::instr()
{
  return hw::Instr_t::INC_NEi;
}

void hw::INC_NEiInstr::build_ir(uint32_t PC, ir_data data)
{
  Value *arg1_p = GEP2_32(_r2, data.regFile, data.builder);
  Value *arg1 =
      data.builder.CreateAdd(data.builder.CreateLoad(Type::getInt32Ty(data.builder.getContext()), arg1_p), data.builder.getInt32(1));
  data.builder.CreateStore(arg1, arg1_p);
 data.builder.CreateStore(data.builder.CreateICmpNE(arg1, data.builder.getInt32(_r3)),
    GEP2_32(_r1, data.regFile, data.builder));
}

void hw::SUBiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] - _r3;
}

void hw::SUBiInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateSub(load(_r2, data.regFile, data.builder), data.builder.getInt32(_r3)),GEP2_32(_r1, data.regFile, data.builder));
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

void hw::BR_CONDInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateCondBr(
          data.builder.CreateTrunc(load(_r1, data.regFile, data.builder), data.builder.getInt1Ty()),
          data.BBMap[_r2], data.BBMap[PC + 1]);
      data.builder.SetInsertPoint(data.BBMap[PC + 1]);
      ___temp = true;
}

void hw::PUT_PIXELInstr::execute(CPU& cpu)
{
  simPutPixel(cpu.m_regFile[_r1], cpu.m_regFile[_r2], cpu.m_regFile[_r3]); 
}

hw::Instr_t hw::PUT_PIXELInstr::instr()
{
  return hw::Instr_t::PUT_PIXEL;
}

void hw::PUT_PIXELInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateCall(data.FuncMap.at("simPutPixelFunc"), {load(_r1, data.regFile, data.builder), load(_r2, data.regFile, data.builder), load(_r3, data.regFile, data.builder)});
}


void hw::FLUSHInstr::execute(CPU& cpu)
{
  simFlush();
}

hw::Instr_t hw::FLUSHInstr::instr()
{
  return hw::Instr_t::FLUSH;
}

void hw::FLUSHInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateCall(data.FuncMap.at("simFlushFunc"));
}

void hw::EXITInstr::execute(CPU& cpu)
{
  cpu.m_run = 0;
}

hw::Instr_t hw::EXITInstr::instr()
{
  return hw::Instr_t::EXIT;
}

void hw::EXITInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateRetVoid();
}

void hw::RANDInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = static_cast<uint32_t>(simRand());
}

hw::Instr_t hw::RANDInstr::instr()
{
  return hw::Instr_t::RAND;
}

void hw::RANDInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateCall(data.FuncMap.at("simRandFunc")), GEP2_32(_r1, data.regFile, data.builder));
}

