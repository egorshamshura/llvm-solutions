#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace hw {

struct CPU;

struct ir_data
{
  IRBuilder<>& builder;
  GlobalVariable *regFile;
  std::unordered_map<uint32_t, BasicBlock*>& BBMap;
  std::unordered_map<std::string, FunctionCallee>& FuncMap;
};

enum class Instr_t
{
  EQi,
  ADD,
  ADDi,
  AND,
  ANDi,
  SUB,
  MUL,
  DIV,
  REM,
  XOR,
  INC_NEi,
  SUBi,
  PUT_PIXEL,
  READ,
  WRITE64,
  WRITE64ii,
  WRITE64ri,
  BR_COND,
  FLUSH,
  RAND,
  ALLOC,
  DUMP,
  EXIT,
};

static std::unordered_map<std::string, Instr_t> str2Instr = {
  {"EQi", Instr_t::EQi},
  {"ADD", Instr_t::ADD},
  {"ADDi", Instr_t::ADDi},
  {"AND", Instr_t::AND},
  {"ANDi", Instr_t::ANDi},
  {"SUB", Instr_t::SUB},
  {"MUL", Instr_t::MUL},
  {"DIV", Instr_t::DIV},
  {"REM", Instr_t::REM},
  {"XOR", Instr_t::XOR},
  {"INC_NEi", Instr_t::INC_NEi},
  {"SUBi", Instr_t::SUBi},
  {"PUT_PIXEL", Instr_t::PUT_PIXEL},
  {"BR_COND", Instr_t::BR_COND},
  {"FLUSH", Instr_t::FLUSH},
  {"RAND", Instr_t::RAND},
  {"ALLOC", Instr_t::ALLOC},
  {"READ", Instr_t::READ},
  {"WRITE64", Instr_t::WRITE64},
  {"WRITE64ii", Instr_t::WRITE64ii},
  {"WRITE64ri", Instr_t::WRITE64ri},
  {"DUMP", Instr_t::DUMP},
  {"EXIT", Instr_t::EXIT},
};
static std::unordered_map<Instr_t, std::string> instr2Str;

struct Instruction
{
  virtual void execute(CPU&) = 0;
  virtual Instr_t instr() = 0;
  virtual void build_ir(uint32_t PC, ir_data) = 0;
};

/* Binary operations */
struct BinaryOperator : Instruction
{
  BinaryOperator(uint32_t r1, uint32_t r2, uint32_t r3) 
    : _r1(r1), _r2(r2), _r3(r3) {}

  uint32_t _r1;
  uint32_t _r2;
  uint32_t _r3;
};

struct EQiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct ADDInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct ADDiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct ANDiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct ANDInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};


struct SUBInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct MULInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct DIVInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct REMInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct XORInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct INC_NEiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct SUBiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct PUT_PIXELInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct READInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct WRITE64Instr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct WRITE64iiInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct WRITE64riInstr : BinaryOperator
{
  using BinaryOperator::BinaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};
/* ---------------- */

/* Unary operations */
struct UnaryOperator : Instruction
{
  UnaryOperator(uint32_t r1, uint32_t r2)
    : _r1(r1), _r2(r2) {}

  uint32_t _r1;
  uint32_t _r2;
};

struct BR_CONDInstr : UnaryOperator
{
  using UnaryOperator::UnaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct ALLOCInstr : UnaryOperator
{
  using UnaryOperator::UnaryOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};
/* ---------------------- */

/* ZeroArity instructions */
struct ZeroArityOperator : Instruction
{
  ZeroArityOperator(uint32_t r1)
    : _r1(r1) {}

  uint32_t _r1;
};

struct RANDInstr : ZeroArityOperator
{
  using ZeroArityOperator::ZeroArityOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct DUMPInstr : ZeroArityOperator
{
  using ZeroArityOperator::ZeroArityOperator;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

/* ------------------- */

/* Invoke instructions */
struct InvokeInst : Instruction
{};

struct FLUSHInstr : InvokeInst
{
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

struct EXITInstr : InvokeInst
{
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint32_t, ir_data) override;
};

}; // namespace hw