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
    llvm::Value *Cmp = std::any_cast<llvm::Value*>(visit(ctx->cond_expr()));
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
    } else if (ctx->INT()) {
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*ctxLLVM), std::stoll(ctx->INT()->getText())));
    } else if (ctx->ID()) {
        return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    } else if (ctx->funcCall()) {
        return visit(ctx->funcCall());
    } else if (ctx->MUL() && ctx->primary_expr().size() == 2) {
        return static_cast<llvm::Value*>(builder->CreateMul(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    } else if (ctx->DIV()) {
        return static_cast<llvm::Value*>(builder->CreateUDiv(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    } else if (ctx->ADD()) {
        return static_cast<llvm::Value*>(builder->CreateAdd(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->SUB() && ctx->primary_expr().size() == 2) {
        return static_cast<llvm::Value*>(builder->CreateSub(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->AND()) {
        return static_cast<llvm::Value*>(builder->CreateAnd(std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0))), std::any_cast<llvm::Value*>(visit(ctx->primary_expr(1)))));
    }
    if (ctx->LPAREN()) {
        return std::any_cast<llvm::Value*>(visit(ctx->primary_expr(0)));
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
    llvm::Value *i = builder->CreateAlloca(llvm::Type::getInt8Ty(*ctxLLVM), builder->getInt32(std::stoi(ctx->INT()->getText()) * 8));
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
        indexValue = builder->getInt32(index);
    } else {
        indexValue = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(1)->getText()]);
    }
    llvm::Value* final_ptr = builder->CreateGEP(llvm::Type::getInt8Ty(*ctxLLVM), varsInFuncs[currFunc][varName], builder->CreateMul(indexValue, builder->getInt32(4)));
    return builder->CreateStore(loaded, builder->CreateIntToPtr(final_ptr, builder->getInt8Ty()->getPointerTo()));
}

std::any hw5::SimpleLangVisitor::visitGetElementArray(hw5::SimpleLangParser::GetElementArrayContext *ctx) {
    std::string varName = ctx->ID(0)->getText();
    llvm::Value* indexValue;
    if (ctx->INT()) {
        int index = std::stoi(ctx->INT()->getText());
        indexValue = builder->getInt32(index);
    } else {
        indexValue = builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID(1)->getText()]);
    }
    llvm::Value* final_ptr = builder->CreateGEP(llvm::Type::getInt8Ty(*ctxLLVM), varsInFuncs[currFunc][varName], builder->CreateMul(indexValue, builder->getInt32(4)));

    return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), builder->CreateIntToPtr(final_ptr, builder->getInt8Ty()->getPointerTo())));
}