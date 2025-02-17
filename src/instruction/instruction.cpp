#include "instruction.h"
#include "lib/sim.h"
#include "cpu/cpu.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/InstrTypes.h>
#include <iostream>

extern bool ___temp;

namespace
{

Value* GEP2_32(uint32_t arg, GlobalVariable *regFile, IRBuilder<> &builder) 
{
  ArrayType *regFileType = ArrayType::get(Type::getInt32Ty(builder.getContext()), hw::constant::REG_SIZE);
  return builder.CreateConstGEP2_32(regFileType, regFile, 0, arg);
}

Value* GEP2_64(uint32_t arg, GlobalVariable *regFile, IRBuilder<> &builder) 
{
  ArrayType *regFileType = ArrayType::get(Type::getInt64Ty(builder.getContext()), hw::constant::REG_SIZE);
  return builder.CreateConstGEP2_64(regFileType, regFile, 0, arg);
}

LoadInst* load64(uint32_t arg, GlobalVariable *regFile, IRBuilder<> &builder)
{
  return builder.CreateLoad(Type::getInt64Ty(builder.getContext()), GEP2_64(arg, regFile, builder));
}
} // anonymous namespace

void hw::EQiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = static_cast<uint32_t>(cpu.m_regFile[_r2] == _r3);
}

hw::Instr_t hw::EQiInstr::instr()
{
  return hw::Instr_t::EQi;
}

void hw::EQiInstr::build_ir(uint32_t PC, ir_data data)
{
  auto* r2_value = load64(_r2, data.regFile, data.builder);
  auto* r3_value = data.builder.getInt64(_r3);
  auto* comparison = data.builder.CreateICmpEQ(r2_value, r3_value);
  auto* result = data.builder.CreateZExt(comparison, Type::getInt64Ty(data.builder.getContext()));
  auto* r1_ptr = GEP2_64(_r1, data.regFile, data.builder);
  data.builder.CreateStore(result, r1_ptr);
}

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
  data.builder.CreateStore(data.builder.CreateAdd(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
}

void hw::ANDiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] & _r3;
}

hw::Instr_t hw::ANDiInstr::instr()
{
  return hw::Instr_t::ANDi;
}

void hw::ANDiInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateAnd(load64(_r2, data.regFile, data.builder), data.builder.getInt64(_r3)),GEP2_64(_r1, data.regFile, data.builder));
}

void hw::ANDInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] & cpu.m_regFile[_r3];
}

hw::Instr_t hw::ANDInstr::instr()
{
  return hw::Instr_t::AND;
}

void hw::ANDInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateAnd(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)),GEP2_64(_r1, data.regFile, data.builder));
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
  data.builder.CreateStore(data.builder.CreateSub(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
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
  data.builder.CreateStore(data.builder.CreateMul(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
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
  data.builder.CreateStore(data.builder.CreateSDiv(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
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
  data.builder.CreateStore(data.builder.CreateSRem(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
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
  data.builder.CreateStore(data.builder.CreateXor(load64(_r2, data.regFile, data.builder), load64(_r3, data.regFile, data.builder)), GEP2_64(_r1, data.regFile, data.builder));
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
  Value *arg1_p = GEP2_64(_r2, data.regFile, data.builder);
  auto& ctx = data.builder.getContext();
  Value *load = data.builder.CreateLoad(data.builder.getInt64Ty(), arg1_p);
  Value *arg1 =
      data.builder.CreateAdd(load, data.builder.getInt64(1));
  data.builder.CreateStore(arg1, arg1_p);
  data.builder.CreateStore(data.builder.CreateICmpNE(arg1, data.builder.getInt64(_r3)),
    GEP2_64(_r1, data.regFile, data.builder));
}

void hw::SUBiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] - _r3;
}

void hw::SUBiInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateSub(load64(_r2, data.regFile, data.builder), data.builder.getInt64(_r3)),GEP2_64(_r1, data.regFile, data.builder));
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
          data.builder.CreateTrunc(load64(_r1, data.regFile, data.builder), data.builder.getInt1Ty()),
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
  data.builder.CreateCall(data.FuncMap.at("simPutPixelFunc"), {
    data.builder.CreateIntCast(load64(_r1, data.regFile, data.builder), Type::getInt32Ty(data.builder.getContext()), false), 
    data.builder.CreateIntCast(load64(_r2, data.regFile, data.builder), Type::getInt32Ty(data.builder.getContext()), false), 
    data.builder.CreateIntCast(load64(_r3, data.regFile, data.builder), Type::getInt32Ty(data.builder.getContext()), false)});
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
  data.builder.CreateStore(data.builder.CreateIntCast(data.builder.CreateCall(data.FuncMap.at("simRandFunc")), Type::getInt64Ty(data.builder.getContext()), false), GEP2_64(_r1, data.regFile, data.builder));
}

void hw::ALLOCInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_mem_idx;
  cpu.m_mem_idx += _r2 / 4;
}

hw::Instr_t hw::ALLOCInstr::instr()
{
  return hw::Instr_t::ALLOC;
}

void hw::ALLOCInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateAlloca(Type::getInt32Ty(data.builder.getContext()), data.builder.getInt32(_r2)), GEP2_32(_r1, data.regFile, data.builder));
}

void hw::READInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_mem[cpu.m_regFile[_r2] + cpu.m_regFile[_r3]];
}

hw::Instr_t hw::READInstr::instr()
{
  return hw::Instr_t::READ;
}

void hw::READInstr::build_ir(uint32_t PC, ir_data data)
{
  auto* base_ptr = load64(_r2, data.regFile, data.builder);
  auto* offset = load64(_r3, data.regFile, data.builder);
  auto* final_ptr = data.builder.CreateAdd(base_ptr, offset);
  auto* loaded_value = data.builder.CreateLoad(Type::getInt32Ty(data.builder.getContext()), data.builder.CreateIntToPtr(final_ptr, data.builder.getInt8Ty()->getPointerTo()));
  data.builder.CreateStore(loaded_value, GEP2_32(_r1, data.regFile, data.builder));
}

void hw::WRITEInstr::execute(CPU& cpu)
{
  cpu.m_mem[cpu.m_regFile[_r1] + cpu.m_regFile[_r2]] = cpu.m_regFile[_r3];
}

hw::Instr_t hw::WRITEInstr::instr()
{
  return hw::Instr_t::WRITE;
}

void hw::WRITEInstr::build_ir(uint32_t PC, ir_data data)
{
  auto* offset = load64(_r2, data.regFile, data.builder);
  auto* r3 = load64(_r3, data.regFile, data.builder);
  auto* mem_ptr = load64(_r1, data.regFile, data.builder);
  auto* final_ptr = data.builder.CreateAdd(mem_ptr, offset);
  data.builder.CreateStore(r3, data.builder.CreateIntToPtr(final_ptr, data.builder.getInt8Ty()->getPointerTo()));
}

void hw::WRITEiInstr::execute(CPU& cpu)
{
  cpu.m_mem[cpu.m_regFile[_r1] + _r2 / 4] = _r3;
}

hw::Instr_t hw::WRITEiInstr::instr()
{
  return hw::Instr_t::WRITEi;
}

void hw::WRITEiInstr::build_ir(uint32_t PC, ir_data data)
{
  auto* mem_ptr = load64(_r1, data.regFile, data.builder);
  auto* offset = data.builder.getInt32(_r2);  
  auto* r3 = load64(_r3, data.regFile, data.builder);
  auto* final_ptr = data.builder.CreateAdd(mem_ptr, offset);
  data.builder.CreateStore(r3, data.builder.CreateIntToPtr(final_ptr, data.builder.getInt8Ty()->getPointerTo()));
}

void hw::WRITEriInstr::execute(CPU& cpu)
{
  cpu.m_mem[cpu.m_regFile[_r1] + cpu.m_regFile[_r2] / 4] = _r3;
}

hw::Instr_t hw::WRITEriInstr::instr()
{
  return hw::Instr_t::WRITEri;
}

void hw::WRITEriInstr::build_ir(uint32_t PC, ir_data data)
{
  auto* mem_ptr = load64(_r1, data.regFile, data.builder);
  auto* offset = load64(_r2, data.regFile, data.builder);
  auto* r3 = load64(_r3, data.regFile, data.builder);
  auto* final_ptr = data.builder.CreateAdd(mem_ptr, offset);
  data.builder.CreateStore(r3, data.builder.CreateIntToPtr(final_ptr, data.builder.getInt8Ty()->getPointerTo()));
}

void hw::ADDiInstr::execute(CPU& cpu)
{
  cpu.m_regFile[_r1] = cpu.m_regFile[_r2] + _r3;
}

hw::Instr_t hw::ADDiInstr::instr()
{
  return hw::Instr_t::ADDi;
}

void hw::ADDiInstr::build_ir(uint32_t PC, ir_data data)
{
  data.builder.CreateStore(data.builder.CreateAdd(load64(_r2, data.regFile, data.builder), data.builder.getInt64(_r3)), GEP2_64(_r1, data.regFile, data.builder));
}