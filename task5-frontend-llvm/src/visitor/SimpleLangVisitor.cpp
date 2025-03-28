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

void hw5::SimpleLangVisitor::generateIfOrWhile(hw5::SimpleLangParser::Expr_lineContext *ctx, bool isIf) {
    llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    llvm::BasicBlock *BodyBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    llvm::BasicBlock *EndBB = llvm::BasicBlock::Create(*ctxLLVM, "BB", functions[currFunc]);
    builder->CreateBr(CondBB);
    builder->SetInsertPoint(CondBB);
    llvm::Value *Cmp = builder->CreateICmpSLT(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->cond_expr()->ID(0)->getText()]), builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->cond_expr()->ID(1)->getText()]));
    builder->CreateCondBr(Cmp, BodyBB, EndBB);
    builder->SetInsertPoint(BodyBB);
    visit(ctx->expr());
    builder->CreateBr(isIf ? EndBB : CondBB);
    builder->SetInsertPoint(EndBB);
}

std::any hw5::SimpleLangVisitor::visitExpr_line(hw5::SimpleLangParser::Expr_lineContext *ctx)
{
    if (ctx->allocateArray()) {
        visit(ctx->allocateArray());
    }
    if (ctx->setElementArray()) {
        visit(ctx->setElementArray());
    }
    if (ctx->varDecl()) {
        visit(ctx->varDecl());
    }
    if (ctx->ID()) {
        builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->primary_expr())), varsInFuncs[currFunc][ctx->ID()->getText()]);
    }
    if (ctx->funcCall())
        visit(ctx->funcCall());
    if (ctx->IF()) {
        generateIfOrWhile(ctx, true);
    }
    if (ctx->WHILE()) {    
        generateIfOrWhile(ctx, false);    
    }
    if (ctx->RETURN()) {
        builder->CreateRet(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    }
    return "";
}

std::any hw5::SimpleLangVisitor::visitVarDecl(hw5::SimpleLangParser::VarDeclContext *ctx)
{
    std::string varName = ctx->ID()->getText();
    auto x = builder->GetInsertBlock();
    builder->SetInsertPoint(currEntryBB);
    llvm::Value *i = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), nullptr);
    builder->SetInsertPoint(x);
    varsInFuncs[currFunc][varName] = i;
    builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->primary_expr())), i);
    return varsInFuncs[currFunc][varName];
}

std::any hw5::SimpleLangVisitor::visitFuncCall(hw5::SimpleLangParser::FuncCallContext *ctx)
{
    std::vector<llvm::Value*> args;
    for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
        args.push_back(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][std::string(ctx->funcArgs()->ID(arg)->getText())]));
    }
    return static_cast<llvm::Value*>(builder->CreateCall(module->getFunction(ctx->ID()->getText()), args));
}

std::any hw5::SimpleLangVisitor::visitPrimary_expr(hw5::SimpleLangParser::Primary_exprContext *ctx)
{
    if (ctx->getElementArray()) {
        return visit(ctx->getElementArray());
    }
    if (ctx->INT()) {
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*ctxLLVM), std::stoll(ctx->INT()->getText())));
    }
    if (ctx->ID()) {
        return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    }
    if (ctx->funcCall()) {
        return visit(ctx->funcCall());
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
    if (ctx->AND()) {
        return static_cast<llvm::Value*>(builder->CreateAnd(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    return static_cast<llvm::Value*>(builder->CreateNeg(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0)))));
}

std::any hw5::SimpleLangVisitor::visitCond_expr(hw5::SimpleLangParser::Cond_exprContext *ctx) {
    llvm::Value* loaded1 = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(0)->getText()]);
    llvm::Value* loaded2 = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(1)->getText()]);
    if (ctx->LESS()) {
        return static_cast<llvm::Value*>(builder->CreateICmpSLT(loaded1, loaded2));
    }
    if (ctx->GREATER()) {
        return static_cast<llvm::Value*>(builder->CreateICmpSGT(loaded1, loaded2));
    }
    if (ctx->NOTLESS()) {
        return static_cast<llvm::Value*>(builder->CreateICmpSGE(loaded1, loaded2));
    }
    if (ctx->NOTGREATER()) {
        return static_cast<llvm::Value*>(builder->CreateICmpSLE(loaded1, loaded2));
    }
    if (ctx->EQUALS()) {
        return static_cast<llvm::Value*>(builder->CreateICmpEQ(loaded1, loaded2));
    }
    return static_cast<llvm::Value*>(builder->CreateICmpNE(loaded1, loaded2));
}

std::any hw5::SimpleLangVisitor::visitAllocateArray(hw5::SimpleLangParser::AllocateArrayContext *ctx) {
    std::string varName = ctx->ID()->getText();
    auto x = builder->GetInsertBlock();
    builder->SetInsertPoint(currEntryBB);
    llvm::Value *i = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), builder->getInt32(std::stoi(ctx->INT()->getText())));
    builder->SetInsertPoint(x);
    varsInFuncs[currFunc][varName] = i;
    return varsInFuncs[currFunc][varName];
}

std::any hw5::SimpleLangVisitor::visitSetElementArray(hw5::SimpleLangParser::SetElementArrayContext *ctx) {
    std::string varName = ctx->ID(0)->getText();
    llvm::Value* loaded = std::any_cast<llvm::Value*>(visit(ctx->primary_expr()));
    llvm::Value* indexValue;
    if (ctx->INT()) {
        int index = std::stoi(ctx->INT()->getText());
        indexValue = builder->getInt64(index);
    } else {
        indexValue = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(1)->getText()]);
    }
    llvm::Value* final_ptr = builder->CreateGEP(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][varName], indexValue);
    return builder->CreateStore(loaded, final_ptr);
}

std::any hw5::SimpleLangVisitor::visitGetElementArray(hw5::SimpleLangParser::GetElementArrayContext *ctx) {
    std::string varName = ctx->ID(0)->getText();
    llvm::Value* indexValue;
    if (ctx->INT()) {
        int index = std::stoi(ctx->INT()->getText());
        indexValue = builder->getInt64(index);
    } else {
        indexValue = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(1)->getText()]);
    }
    llvm::Value* final_ptr = builder->CreateGEP(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][varName], indexValue);
    
    return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), final_ptr));
}