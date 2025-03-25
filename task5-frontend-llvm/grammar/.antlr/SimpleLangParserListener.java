// Generated from /root/llvm-solutions/solutions/task5-frontend-llvm/grammar/SimpleLangParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link SimpleLangParser}.
 */
public interface SimpleLangParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#main}.
	 * @param ctx the parse tree
	 */
	void enterMain(SimpleLangParser.MainContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#main}.
	 * @param ctx the parse tree
	 */
	void exitMain(SimpleLangParser.MainContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#funcDecl}.
	 * @param ctx the parse tree
	 */
	void enterFuncDecl(SimpleLangParser.FuncDeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#funcDecl}.
	 * @param ctx the parse tree
	 */
	void exitFuncDecl(SimpleLangParser.FuncDeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#funcName}.
	 * @param ctx the parse tree
	 */
	void enterFuncName(SimpleLangParser.FuncNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#funcName}.
	 * @param ctx the parse tree
	 */
	void exitFuncName(SimpleLangParser.FuncNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#funcArgs}.
	 * @param ctx the parse tree
	 */
	void enterFuncArgs(SimpleLangParser.FuncArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#funcArgs}.
	 * @param ctx the parse tree
	 */
	void exitFuncArgs(SimpleLangParser.FuncArgsContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#return_type}.
	 * @param ctx the parse tree
	 */
	void enterReturn_type(SimpleLangParser.Return_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#return_type}.
	 * @param ctx the parse tree
	 */
	void exitReturn_type(SimpleLangParser.Return_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#funcBody}.
	 * @param ctx the parse tree
	 */
	void enterFuncBody(SimpleLangParser.FuncBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#funcBody}.
	 * @param ctx the parse tree
	 */
	void exitFuncBody(SimpleLangParser.FuncBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(SimpleLangParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(SimpleLangParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#expr_line}.
	 * @param ctx the parse tree
	 */
	void enterExpr_line(SimpleLangParser.Expr_lineContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#expr_line}.
	 * @param ctx the parse tree
	 */
	void exitExpr_line(SimpleLangParser.Expr_lineContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#varDecl}.
	 * @param ctx the parse tree
	 */
	void enterVarDecl(SimpleLangParser.VarDeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#varDecl}.
	 * @param ctx the parse tree
	 */
	void exitVarDecl(SimpleLangParser.VarDeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#funcCall}.
	 * @param ctx the parse tree
	 */
	void enterFuncCall(SimpleLangParser.FuncCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#funcCall}.
	 * @param ctx the parse tree
	 */
	void exitFuncCall(SimpleLangParser.FuncCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#primary_expr}.
	 * @param ctx the parse tree
	 */
	void enterPrimary_expr(SimpleLangParser.Primary_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#primary_expr}.
	 * @param ctx the parse tree
	 */
	void exitPrimary_expr(SimpleLangParser.Primary_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link SimpleLangParser#cond_expr}.
	 * @param ctx the parse tree
	 */
	void enterCond_expr(SimpleLangParser.Cond_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link SimpleLangParser#cond_expr}.
	 * @param ctx the parse tree
	 */
	void exitCond_expr(SimpleLangParser.Cond_exprContext ctx);
}