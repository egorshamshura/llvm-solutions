#include "SimpleLangVisitor.h"
#include <algorithm>
#include <llvm/IR/Type.h>

std::any hw5::SimpleLangVisitor::visitMain(hw5::SimpleLangParser::MainContext *ctx)
{
    for (size_t i = 0; i != ctx->funcDecl().size(); ++i)
        visit(ctx->funcDecl(i));
    return functions["app"];
}

std::any hw5::SimpleLangVisitor::visitFuncDecl(hw5::SimpleLangParser::FuncDeclContext *ctx) 
{
    std::string functionName = std::string(ctx->funcName()->ID()->getText());
    currFunc = functionName;
    varsInFuncs.insert({functionName, {}});
    std::vector<llvm::Type*> funcParamTypes(ctx->funcArgs()->ID().size(), llvm::Type::getInt32Ty(*ctxLLVM));
    llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*ctxLLVM), funcParamTypes, false);
    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, functionName, module);
    functions[currFunc] = func;
    llvm::BasicBlock *allocsBB = llvm::BasicBlock::Create(*ctxLLVM, "allocs", func);
    builder->SetInsertPoint(allocsBB);
    currEntryBB = builder->GetInsertBlock();
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(*ctxLLVM, "entry", func);
    builder->SetInsertPoint(entryBB);
    for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
        varsInFuncs[functionName][ctx->funcArgs()->ID(arg)->getText()] = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), nullptr);
        builder->CreateStore(static_cast<llvm::Value*>(func->getArg(arg)), varsInFuncs[functionName][ctx->funcArgs()->ID(arg)->getText()]);
    }
    visit(ctx->funcBody());
    auto x = builder->GetInsertBlock();
    builder->SetInsertPoint(allocsBB);
    builder->CreateBr(entryBB);
    builder->SetInsertPoint(x);
    builder->CreateRet(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    return "";
}

std::any hw5::SimpleLangVisitor::visitFuncBody(hw5::SimpleLangParser::FuncBodyContext *ctx)
{
    visit(ctx->expr());
    return "";
}

std::any hw5::SimpleLangVisitor::visitExpr(hw5::SimpleLangParser::ExprContext *ctx) 
{
    for (size_t i = 0; i != ctx->expr_line().size(); ++i)
        visit(ctx->expr_line(i));
    return "";
}

void hw5::SimpleLangVisitor::generateWhile(hw5::SimpleLangParser::Expr_lineContext *ctx) {
    llvm::BasicBlock *WhileCondBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    llvm::BasicBlock *WhileBodyBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    llvm::BasicBlock *WhileEndBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    builder->CreateBr(WhileCondBB);
    builder->SetInsertPoint(WhileCondBB);
    llvm::Value *Cmp = builder->CreateICmpSLT(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->cond_expr()->ID(0)->getText()]), builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->cond_expr()->ID(1)->getText()]));
    builder->CreateCondBr(Cmp, WhileBodyBB, WhileEndBB);
    builder->SetInsertPoint(WhileBodyBB);
    visit(ctx->expr());
    builder->CreateBr(WhileCondBB);
    builder->SetInsertPoint(WhileEndBB);
}

std::any hw5::SimpleLangVisitor::visitExpr_line(hw5::SimpleLangParser::Expr_lineContext *ctx)
{
    if (ctx->varDecl()) {
        std::string varName = ctx->varDecl()->ID()->getText();
        currVarName = varName;
        auto x = builder->GetInsertBlock();
        builder->SetInsertPoint(currEntryBB);
        llvm::Value *i = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), nullptr);
        builder->SetInsertPoint(x);
        varsInFuncs[currFunc][currVarName] = i;
        builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->varDecl()->primary_expr())), i);
    }
    if (ctx->ID()) {
        builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->primary_expr())), varsInFuncs[currFunc][ctx->ID()->getText()]);
    }
    if (ctx->funcCall())
        visit(ctx->funcCall());
    if (ctx->cond_expr()) {    
        generateWhile(ctx);    
    }
    return "";
}

std::any hw5::SimpleLangVisitor::visitVarDecl(hw5::SimpleLangParser::VarDeclContext *ctx)
{
    varsInFuncs[currFunc][currVarName] = std::any_cast<llvm::Value*>(visit(ctx->primary_expr()));
    return varsInFuncs[currFunc][currVarName];
}

std::any hw5::SimpleLangVisitor::visitFuncCall(hw5::SimpleLangParser::FuncCallContext *ctx)
{
    return generateFuncCall(ctx);
}

std::any hw5::SimpleLangVisitor::visitPrimary_expr(hw5::SimpleLangParser::Primary_exprContext *ctx)
{
    if (ctx->INT()) {
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*ctxLLVM), std::stoi(ctx->INT()->getText())));
    }
    if (ctx->ID() && !ctx->funcArgs()) {
        return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    }
    if (ctx->ID() && ctx->funcArgs()) {
        return generateFuncCall(ctx);
    }
    if (ctx->MUL() && ctx->primary_expr().size() == 2) {
        return static_cast<llvm::Value*>(builder->CreateMul(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->DIV()) {
        return static_cast<llvm::Value*>(builder->CreateSDiv(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->ADD()) {
        return static_cast<llvm::Value*>(builder->CreateAdd(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->SUB() && ctx->primary_expr().size() == 2) {
        return static_cast<llvm::Value*>(builder->CreateSub(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->SUB() && ctx->primary_expr().size() == 1) {
        return static_cast<llvm::Value*>(builder->CreateNeg(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0)))));
    }
    return "";
}
