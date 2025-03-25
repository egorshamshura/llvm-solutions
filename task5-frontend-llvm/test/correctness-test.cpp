#include "gtest/gtest.h"
#include "llvm/IR/Type.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include <sstream>
#include "llvm/IR/Verifier.h"

#include "visitor/SimpleLangVisitor.h"
#include "SimpleLangLexer.h"
#include "SimpleLangParser.h"
#include "Token.h"
#include "lib/sim.h"

TEST(simplelang, simple)
{
    std::ifstream stream("test/app1");
    antlr4::ANTLRInputStream input(stream);

    hw5::SimpleLangLexer lexer(&input);

    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    hw5::SimpleLangParser parser(&tokens);

    hw5::SimpleLangParser::MainContext* tree = parser.main();

    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module *module = new llvm::Module("app.c", context);
    hw5::SimpleLangVisitor vis(&context, &builder, module);

    llvm::ArrayRef<llvm::Type*> simPutPixelParamTypes = {llvm::Type::getInt32Ty(context), llvm::Type::getInt32Ty(context), llvm::Type::getInt32Ty(context)};
    llvm::FunctionType *simPutPixelType =
    llvm::FunctionType::get(llvm::Type::getInt32Ty(context), simPutPixelParamTypes, false);
    module->getOrInsertFunction("put_pixel", simPutPixelType);
    llvm::ArrayRef<llvm::Type*> simFlushParamTypes = {};
    llvm::FunctionType *simFlushType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), simFlushParamTypes, false);
    module->getOrInsertFunction("flush", simFlushType);
    llvm::ArrayRef<llvm::Type*> dumpParamTypes = {llvm::Type::getInt32Ty(context)};
    llvm::FunctionType *dumpType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), dumpParamTypes, false);
    module->getOrInsertFunction("dump", dumpType);
    llvm::Function* app = std::any_cast<llvm::Function*>(vis.visitMain(tree));
    llvm::outs() << "[LLVM IR]\n";
    module->print(llvm::outs(), nullptr);
    llvm::outs() << "\n";
    bool verif = llvm::verifyModule(*module, &llvm::outs());
    llvm::outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();

    llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
    ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
        if (fnName == "put_pixel") {
            return reinterpret_cast<void *>(simPutPixel);
        }
        if (fnName == "flush") {
            return reinterpret_cast<void *>(simFlush);
        }
        if (fnName == "dump") {
            return reinterpret_cast<void *>(dump);
        }
        return nullptr;
    });
    ee->finalizeObject();

    simInit();

    llvm::ArrayRef<llvm::GenericValue> noargs;
    llvm::outs() << "\n#[Running code]\n";
    llvm::GenericValue v = ee->runFunction(app, noargs);
    llvm::outs() << "#[Code was run]\n";
    simExit();
}