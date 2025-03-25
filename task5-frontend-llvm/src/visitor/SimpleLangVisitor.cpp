#include "SimpleLangVisitor.h"
#include <llvm-18/llvm/IR/Type.h>

std::any hw5::SimpleLangVisitor::visitMain(hw5::SimpleLangParser::MainContext *ctx)
{
    llvm::outs() << "visitMain:\n";
    for (size_t i = 0; i != ctx->funcDecl().size(); ++i)
        visit(ctx->funcDecl(i));
    return functions["main"];
}

std::any hw5::SimpleLangVisitor::visitFuncDecl(hw5::SimpleLangParser::FuncDeclContext *ctx) 
{
    llvm::outs() << "visitFuncDecl:\n";
    std::string functionName = std::string(ctx->funcName()->ID()->getText());
    currFunc = functionName;
    varsInFuncs.insert({functionName, {}});
    std::vector<llvm::Type*> funcParamTypes;
    for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
      funcParamTypes.push_back(llvm::Type::getInt32Ty(*ctxLLVM));
    }
    llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*ctxLLVM), funcParamTypes, false);
    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, functionName, module);
    functions[currFunc] = func;
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(*ctxLLVM, "entry", func);
    builder->SetInsertPoint(entryBB);
    for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
        varsInFuncs[functionName][ctx->funcArgs()->ID(arg)->getText()] = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), nullptr);
        builder->CreateStore(static_cast<llvm::Value*>(func->getArg(arg)), varsInFuncs[functionName][ctx->funcArgs()->ID(arg)->getText()]);
    }
    visit(ctx->funcBody());

    visit(ctx->funcArgs());
    visit(ctx->return_type());
    builder->CreateRet(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    return "";
}

std::any hw5::SimpleLangVisitor::visitFuncArgs(hw5::SimpleLangParser::FuncArgsContext *ctx) 
{
    llvm::outs() << "visitFuncArgs: \n";
    return "";
}

std::any hw5::SimpleLangVisitor::visitReturn_type(hw5::SimpleLangParser::Return_typeContext *ctx)
{
    llvm::outs() << "visitReturn_type: \n";
    return "";
}

std::any hw5::SimpleLangVisitor::visitFuncBody(hw5::SimpleLangParser::FuncBodyContext *ctx)
{
    llvm::outs() << "visitFuncBody: \n";
    visit(ctx->expr());
    return "";
}

std::any hw5::SimpleLangVisitor::visitExpr(hw5::SimpleLangParser::ExprContext *ctx) 
{
    llvm::outs() << "visitExpr: \n";
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
    llvm::outs() << "visitExpr_line: \n";
    if (ctx->varDecl()) {
        std::string varName = ctx->varDecl()->ID()->getText();
        currVarName = varName;
        llvm::Value *i = builder->CreateAlloca(llvm::Type::getInt32Ty(*ctxLLVM), nullptr);
        varsInFuncs[currFunc][currVarName] = i;
        builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->varDecl()->primary_expr())), i);
    }
    if (ctx->ID()) {
        builder->CreateStore(std::any_cast<llvm::Value*>(visit(ctx->primary_expr())), varsInFuncs[currFunc][ctx->ID()->getText()]);
    }
    if (ctx->funcCall())
        visit(ctx->funcCall());
    if (ctx->cond_expr()) {    
        llvm::outs() << "here while: \n";
        generateWhile(ctx);    
    }
    return "";
}

std::any hw5::SimpleLangVisitor::visitVarDecl(hw5::SimpleLangParser::VarDeclContext *ctx)
{
    llvm::outs() << "visitVarDecl: \n";
    varsInFuncs[currFunc][currVarName] = std::any_cast<llvm::Value*>(visit(ctx->primary_expr()));
    return varsInFuncs[currFunc][currVarName];
}

std::any hw5::SimpleLangVisitor::visitFuncCall(hw5::SimpleLangParser::FuncCallContext *ctx)
{
    llvm::outs() << "visitFuncCall: " << ctx->ID()->getText() << "\n";
    std::vector<llvm::Value*> args;
    for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
        args.push_back(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][std::string(ctx->funcArgs()->ID(arg)->getText())]));
    }
    return static_cast<llvm::Value*>(builder->CreateCall(module->getFunction(ctx->ID()->getText()), args));
}

std::any hw5::SimpleLangVisitor::visitPrimary_expr(hw5::SimpleLangParser::Primary_exprContext *ctx)
{
    llvm::outs() << "visitPrimary_expr: \n";
    if (ctx->INT()) {
        llvm::outs() << "int " << std::stoi(ctx->INT()->getText()) << "\n";
        return static_cast<llvm::Value*>(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*ctxLLVM), std::stoi(ctx->INT()->getText())));
    }
    if (ctx->ID() && !ctx->funcArgs()) {
        llvm::outs() << "id " << ctx->ID()->getText() << "\n" ;
        return static_cast<llvm::Value*>(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][ctx->ID()->getText()]));
    }
    if (ctx->ID() && ctx->funcArgs()) {
        llvm::outs() << "func \n";
        std::vector<llvm::Value*> args;
        for (size_t arg = 0; arg != ctx->funcArgs()->ID().size(); ++arg) {
            
            args.push_back(builder->CreateLoad(llvm::Type::getInt32Ty(*ctxLLVM), varsInFuncs[currFunc][std::string(ctx->funcArgs()->ID(arg)->getText())]));
        }
        return static_cast<llvm::Value*>(builder->CreateCall(module->getFunction(ctx->ID()->getText()), args));
    }
    if (ctx->MUL() && ctx->primary_expr().size() == 2) {
        llvm::outs() << "mul \n";
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
