#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "cpu/cpu.h"

namespace hw
{
struct IRGen
{
  void build(Binary&);

  llvm::LLVMContext context;
  llvm::Module *module;
  llvm::Function *mainFunc;
  llvm::GlobalVariable *regFile;
};
} // namespace hw