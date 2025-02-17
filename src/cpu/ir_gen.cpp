#include "ir_gen.h"
#include "instruction/instruction.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include <llvm-18/llvm/Support/raw_ostream.h>
#include "lib/sim.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;
bool ___temp = false;
namespace hw
{
void IRGen::build(Binary& bin) 
{
  module = new Module("top", context);
  IRBuilder<> builder(context);
  Type *voidType = Type::getVoidTy(context);
  Type *int32Type = Type::getInt32Ty(context);
  Type *int64Type = Type::getInt64Ty(context);

  //[16 x i32] regFile = {0, 0, 0, 0}
  ArrayType *regFileType = ArrayType::get(int64Type, constant::REG_SIZE);

  GlobalVariable *regFile = new GlobalVariable(
      *module, regFileType, false, GlobalValue::PrivateLinkage, 0, "regFile");
  regFile->setInitializer(ConstantAggregateZero::get(regFileType));

  // declare void @main()
  FunctionType *funcType = FunctionType::get(voidType, false);
  mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);
  // Funcions types
  FunctionType *voidFuncType = FunctionType::get(voidType, false);
  ArrayRef<Type *> int32x3Types = {int32Type, int32Type, int32Type};
  FunctionType *int32x3FuncType =
      FunctionType::get(voidType, int32x3Types, false);
  

  // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", int32x3FuncType);

  // declare void @simFlush()
  FunctionType *simFlushType = FunctionType::get(voidType, false);
  FunctionCallee simFlushFunc =
      module->getOrInsertFunction("simFlush", simFlushType);

  // declare int @simRand()
  FunctionType *simRandType = FunctionType::get(int32Type, false);
  FunctionCallee simRandFunc =
      module->getOrInsertFunction("simRand", simRandType);

  // declare void @dump(long long)
  FunctionType *dumpType = FunctionType::get(voidType, int64Type, false);
  FunctionCallee dumpFunc =
      module->getOrInsertFunction("dump", dumpType);

  std::unordered_map<uint32_t, BasicBlock*> BBMap;
  std::vector<std::pair<size_t, std::string>> vs;
  for (auto &BB : bin.label2pc) {
    vs.push_back({BB.second, BB.first});
  }
  std::sort(vs.begin(), vs.end(), [](std::pair<size_t, std::string>const& a, std::pair<size_t, std::string> const& b) -> bool {
    return a.first < b.first;
  });
  for (auto &BB : vs) {
    outs() << BB.second << " " << BB.first << '\n';
    BBMap[BB.first] = BasicBlock::Create(context, BB.second, mainFunc);
  }

  std::unordered_map<std::string, FunctionCallee> FuncMap =
    {{"simPutPixelFunc", simPutPixelFunc}, {"simFlushFunc", simFlushFunc},
    {"simRandFunc", simRandFunc}, {"dumpFunc", dumpFunc}};

  uint32_t PC = 0;
  builder.SetInsertPoint(BBMap[0]);
  for (auto& instr: bin.instructions)
  {
    ___temp = false;
    instr->build_ir(PC, {builder, regFile, BBMap, FuncMap});
    ++PC;
    auto BB = BBMap.find(PC);
    if (BB != BBMap.end() && !___temp) {
      builder.CreateBr(BB->second);
      builder.SetInsertPoint(BB->second);
    }
  }
  module->print(outs(), nullptr);
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
}

void IRGen::execute(CPU& cpu)
{
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "simRand") {
      return reinterpret_cast<void *>(simRand);
    }
    if (fnName == "dump") {
      return reinterpret_cast<void *>(dump);
    }
    return nullptr;
  });
  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> noargs;
  outs() << "\n#[Running code]\n";
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";

  simExit();
}
} // namespace hw