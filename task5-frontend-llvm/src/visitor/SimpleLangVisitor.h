#pragma once

#include "SimpleLangParserBaseVisitor.h"
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <any>

namespace hw5 {
struct SimpleLangVisitor : SimpleLangParserBaseVisitor 
{
    explicit SimpleLangVisitor(llvm::LLVMContext *ctxLLVM, llvm::IRBuilder<> *builder, llvm::Module *module)
    : ctxLLVM{ctxLLVM}, builder{builder}, module{module}
    {}

    std::any visitMain(hw5::SimpleLangParser::MainContext *ctx) override;
    std::any visitFuncDecl(hw5::SimpleLangParser::FuncDeclContext *ctx) override;
    std::any visitFuncName(hw5::SimpleLangParser::FuncNameContext *ctx) override { return ""; }
    std::any visitFuncArgs(hw5::SimpleLangParser::FuncArgsContext *ctx) override { return ""; }
    std::any visitReturn_type(hw5::SimpleLangParser::Return_typeContext *ctx) override { return ""; }
    std::any visitFuncBody(hw5::SimpleLangParser::FuncBodyContext *ctx) override;
    std::any visitExpr(hw5::SimpleLangParser::ExprContext *ctx) override;
    std::any visitExpr_line(hw5::SimpleLangParser::Expr_lineContext *ctx) override;
    std::any visitVarDecl(hw5::SimpleLangParser::VarDeclContext *ctx) override;
    std::any visitFuncCall(hw5::SimpleLangParser::FuncCallContext *ctx) override;
    std::any visitPrimary_expr(hw5::SimpleLangParser::Primary_exprContext *ctx) override;

private:
    std::map<std::string, std::map<std::string, llvm::Value*>> varsInFuncs;
    std::map<std::string, llvm::Function*> functions;
    std::string currFunc;
    std::string currVarName;
    llvm::BasicBlock* currEntryBB;
    llvm::LLVMContext *ctxLLVM;
    llvm::IRBuilder<> *builder;
    llvm::Module *module;

    void generateWhile(hw5::SimpleLangParser::Expr_lineContext *ctx);

    template<typename T>
    llvm::Value* generateFuncCall(T* ctx) {
        std::vector<llvm::Value*> args;
        for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
            args.push_back(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][std::string(ctx->funcArgs()->ID(arg)->getText())]));
        }
        return static_cast<llvm::Value*>(builder->CreateCall(module->getFunction(ctx->ID()->getText()), args));
    }
};
} // hw5 namespace