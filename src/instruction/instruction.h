#pragma once

#include "llvm/IR/IRBuilder.h"

#include <cstdint>
#include <string>
#include <unordered_map>

using namespace llvm;

namespace hw {

struct CPU;

struct ir_data {
  IRBuilder<>& builder;
  GlobalVariable* regFile;
  std::unordered_map<uint64_t, BasicBlock*>& BBMap;
  std::unordered_map<std::string, FunctionCallee>& FuncMap;
};

enum class Instr_t {
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
  READ64,
  WRITE64,
  WRITE64ii,
  WRITE64ri,
  BR_COND,
  FLUSH,
  RAND64,
  ALLOC,
  DUMP,
  EXIT,
};

static std::unordered_map<std::string, Instr_t> str2Instr = {
    {      "EQi",       Instr_t::EQi},
    {      "ADD",       Instr_t::ADD},
    {     "ADDi",      Instr_t::ADDi},
    {      "AND",       Instr_t::AND},
    {     "ANDi",      Instr_t::ANDi},
    {      "SUB",       Instr_t::SUB},
    {      "MUL",       Instr_t::MUL},
    {      "DIV",       Instr_t::DIV},
    {      "REM",       Instr_t::REM},
    {      "XOR",       Instr_t::XOR},
    {  "INC_NEi",   Instr_t::INC_NEi},
    {     "SUBi",      Instr_t::SUBi},
    {"PUT_PIXEL", Instr_t::PUT_PIXEL},
    {  "BR_COND",   Instr_t::BR_COND},
    {    "FLUSH",     Instr_t::FLUSH},
    {   "RAND64",    Instr_t::RAND64},
    {    "ALLOC",     Instr_t::ALLOC},
    {   "READ64",    Instr_t::READ64},
    {  "WRITE64",   Instr_t::WRITE64},
    {"WRITE64ii", Instr_t::WRITE64ii},
    {"WRITE64ri", Instr_t::WRITE64ri},
    {     "DUMP",      Instr_t::DUMP},
    {     "EXIT",      Instr_t::EXIT},
};
static std::unordered_map<Instr_t, std::string> instr2Str;

struct Instruction {
  virtual void execute(CPU&) = 0;
  virtual Instr_t instr() = 0;
  virtual void build_ir(uint64_t PC, ir_data) = 0;
};

/* Binary operations */
struct ThreeArityInstruction : Instruction {
  ThreeArityInstruction(uint64_t r1, uint64_t r2, uint64_t r3) : _r1(r1), _r2(r2), _r3(r3) {}

  uint64_t _r1;
  uint64_t _r2;
  uint64_t _r3;
};

struct EQiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct ADDInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct ADDiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct ANDiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct ANDInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct SUBInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct MULInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct DIVInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct REMInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct XORInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct INC_NEiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct SUBiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct PUT_PIXELInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct READ64Instr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct WRITE64Instr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct WRITE64iiInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct WRITE64riInstr : ThreeArityInstruction {
  using ThreeArityInstruction::ThreeArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

/* ---------------- */

/* Unary operations */
struct TwoArityInstruction : Instruction {
  TwoArityInstruction(uint64_t r1, uint64_t r2) : _r1(r1), _r2(r2) {}

  uint64_t _r1;
  uint64_t _r2;
};

struct BR_CONDInstr : TwoArityInstruction {
  using TwoArityInstruction::TwoArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct ALLOCInstr : TwoArityInstruction {
  using TwoArityInstruction::TwoArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

/* ---------------------- */

/* ZeroArity instructions */
struct OneArityInstruction : Instruction {
  OneArityInstruction(uint64_t r1) : _r1(r1) {}

  uint64_t _r1;
};

struct RAND64Instr : OneArityInstruction {
  using OneArityInstruction::OneArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct DUMPInstr : OneArityInstruction {
  using OneArityInstruction::OneArityInstruction;
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

/* ------------------- */

/* Invoke instructions */
struct InvokeInst : Instruction {};

struct FLUSHInstr : InvokeInst {
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

struct EXITInstr : InvokeInst {
  void execute(CPU&) override;
  Instr_t instr() override;
  void build_ir(uint64_t, ir_data) override;
};

}; // namespace hw