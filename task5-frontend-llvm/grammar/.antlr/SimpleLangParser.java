// Generated from /root/llvm-solutions/solutions/task5-frontend-llvm/grammar/SimpleLangParser.g4 by ANTLR 4.13.1
/* parser/listener/visitor header section */
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class SimpleLangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ARROW=1, FUNC=2, LCBRACE=3, RCBRACE=4, LPAREN=5, RPAREN=6, WHILE=7, SUB=8, 
		MUL=9, ADD=10, DIV=11, EQ=12, LESS=13, VAR=14, SEMICOLON=15, RETURN=16, 
		ID=17, INT=18, WS=19;
	public static final int
		RULE_main = 0, RULE_funcDecl = 1, RULE_funcName = 2, RULE_funcArgs = 3, 
		RULE_return_type = 4, RULE_funcBody = 5, RULE_expr = 6, RULE_expr_line = 7, 
		RULE_varDecl = 8, RULE_funcCall = 9, RULE_primary_expr = 10, RULE_cond_expr = 11;
	private static String[] makeRuleNames() {
		return new String[] {
			"main", "funcDecl", "funcName", "funcArgs", "return_type", "funcBody", 
			"expr", "expr_line", "varDecl", "funcCall", "primary_expr", "cond_expr"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'->'", "'func'", "'{'", "'}'", "'('", "')'", "'while'", "'-'", 
			"'*'", "'+'", "'/'", "'='", "'<'", "'var'", "';'", "'return'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "ARROW", "FUNC", "LCBRACE", "RCBRACE", "LPAREN", "RPAREN", "WHILE", 
			"SUB", "MUL", "ADD", "DIV", "EQ", "LESS", "VAR", "SEMICOLON", "RETURN", 
			"ID", "INT", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "SimpleLangParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }



	public SimpleLangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MainContext extends ParserRuleContext {
		public List<FuncDeclContext> funcDecl() {
			return getRuleContexts(FuncDeclContext.class);
		}
		public FuncDeclContext funcDecl(int i) {
			return getRuleContext(FuncDeclContext.class,i);
		}
		public MainContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_main; }
	}

	public final MainContext main() throws RecognitionException {
		MainContext _localctx = new MainContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_main);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(25); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(24);
				funcDecl();
				}
				}
				setState(27); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==FUNC );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncDeclContext extends ParserRuleContext {
		public TerminalNode FUNC() { return getToken(SimpleLangParser.FUNC, 0); }
		public FuncNameContext funcName() {
			return getRuleContext(FuncNameContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(SimpleLangParser.LPAREN, 0); }
		public FuncArgsContext funcArgs() {
			return getRuleContext(FuncArgsContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(SimpleLangParser.RPAREN, 0); }
		public TerminalNode ARROW() { return getToken(SimpleLangParser.ARROW, 0); }
		public Return_typeContext return_type() {
			return getRuleContext(Return_typeContext.class,0);
		}
		public TerminalNode LCBRACE() { return getToken(SimpleLangParser.LCBRACE, 0); }
		public FuncBodyContext funcBody() {
			return getRuleContext(FuncBodyContext.class,0);
		}
		public TerminalNode RETURN() { return getToken(SimpleLangParser.RETURN, 0); }
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public TerminalNode SEMICOLON() { return getToken(SimpleLangParser.SEMICOLON, 0); }
		public TerminalNode RCBRACE() { return getToken(SimpleLangParser.RCBRACE, 0); }
		public FuncDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcDecl; }
	}

	public final FuncDeclContext funcDecl() throws RecognitionException {
		FuncDeclContext _localctx = new FuncDeclContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_funcDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(29);
			match(FUNC);
			setState(30);
			funcName();
			setState(31);
			match(LPAREN);
			setState(32);
			funcArgs();
			setState(33);
			match(RPAREN);
			setState(34);
			match(ARROW);
			setState(35);
			return_type();
			setState(36);
			match(LCBRACE);
			setState(37);
			funcBody();
			setState(38);
			match(RETURN);
			setState(39);
			match(ID);
			setState(40);
			match(SEMICOLON);
			setState(41);
			match(RCBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncNameContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public FuncNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcName; }
	}

	public final FuncNameContext funcName() throws RecognitionException {
		FuncNameContext _localctx = new FuncNameContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_funcName);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncArgsContext extends ParserRuleContext {
		public List<TerminalNode> ID() { return getTokens(SimpleLangParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(SimpleLangParser.ID, i);
		}
		public FuncArgsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcArgs; }
	}

	public final FuncArgsContext funcArgs() throws RecognitionException {
		FuncArgsContext _localctx = new FuncArgsContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_funcArgs);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(48);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==ID) {
				{
				{
				setState(45);
				match(ID);
				}
				}
				setState(50);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Return_typeContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public Return_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_return_type; }
	}

	public final Return_typeContext return_type() throws RecognitionException {
		Return_typeContext _localctx = new Return_typeContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_return_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(51);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncBodyContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public FuncBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcBody; }
	}

	public final FuncBodyContext funcBody() throws RecognitionException {
		FuncBodyContext _localctx = new FuncBodyContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_funcBody);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(53);
			expr();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public List<Expr_lineContext> expr_line() {
			return getRuleContexts(Expr_lineContext.class);
		}
		public Expr_lineContext expr_line(int i) {
			return getRuleContext(Expr_lineContext.class,i);
		}
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_expr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(58);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 147584L) != 0)) {
				{
				{
				setState(55);
				expr_line();
				}
				}
				setState(60);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_lineContext extends ParserRuleContext {
		public VarDeclContext varDecl() {
			return getRuleContext(VarDeclContext.class,0);
		}
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public TerminalNode EQ() { return getToken(SimpleLangParser.EQ, 0); }
		public Primary_exprContext primary_expr() {
			return getRuleContext(Primary_exprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(SimpleLangParser.SEMICOLON, 0); }
		public FuncCallContext funcCall() {
			return getRuleContext(FuncCallContext.class,0);
		}
		public TerminalNode WHILE() { return getToken(SimpleLangParser.WHILE, 0); }
		public TerminalNode LPAREN() { return getToken(SimpleLangParser.LPAREN, 0); }
		public Cond_exprContext cond_expr() {
			return getRuleContext(Cond_exprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(SimpleLangParser.RPAREN, 0); }
		public TerminalNode LCBRACE() { return getToken(SimpleLangParser.LCBRACE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RCBRACE() { return getToken(SimpleLangParser.RCBRACE, 0); }
		public Expr_lineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_line; }
	}

	public final Expr_lineContext expr_line() throws RecognitionException {
		Expr_lineContext _localctx = new Expr_lineContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_expr_line);
		try {
			setState(76);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(61);
				varDecl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(62);
				match(ID);
				setState(63);
				match(EQ);
				setState(64);
				primary_expr(0);
				setState(65);
				match(SEMICOLON);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(67);
				funcCall();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(68);
				match(WHILE);
				setState(69);
				match(LPAREN);
				setState(70);
				cond_expr();
				setState(71);
				match(RPAREN);
				setState(72);
				match(LCBRACE);
				setState(73);
				expr();
				setState(74);
				match(RCBRACE);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarDeclContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(SimpleLangParser.VAR, 0); }
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public TerminalNode EQ() { return getToken(SimpleLangParser.EQ, 0); }
		public Primary_exprContext primary_expr() {
			return getRuleContext(Primary_exprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(SimpleLangParser.SEMICOLON, 0); }
		public VarDeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDecl; }
	}

	public final VarDeclContext varDecl() throws RecognitionException {
		VarDeclContext _localctx = new VarDeclContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_varDecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(78);
			match(VAR);
			setState(79);
			match(ID);
			setState(80);
			match(EQ);
			setState(81);
			primary_expr(0);
			setState(82);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FuncCallContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(SimpleLangParser.LPAREN, 0); }
		public FuncArgsContext funcArgs() {
			return getRuleContext(FuncArgsContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(SimpleLangParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(SimpleLangParser.SEMICOLON, 0); }
		public FuncCallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funcCall; }
	}

	public final FuncCallContext funcCall() throws RecognitionException {
		FuncCallContext _localctx = new FuncCallContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_funcCall);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			match(ID);
			setState(85);
			match(LPAREN);
			setState(86);
			funcArgs();
			setState(87);
			match(RPAREN);
			setState(88);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Primary_exprContext extends ParserRuleContext {
		public TerminalNode SUB() { return getToken(SimpleLangParser.SUB, 0); }
		public List<Primary_exprContext> primary_expr() {
			return getRuleContexts(Primary_exprContext.class);
		}
		public Primary_exprContext primary_expr(int i) {
			return getRuleContext(Primary_exprContext.class,i);
		}
		public TerminalNode LPAREN() { return getToken(SimpleLangParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(SimpleLangParser.RPAREN, 0); }
		public TerminalNode INT() { return getToken(SimpleLangParser.INT, 0); }
		public TerminalNode ID() { return getToken(SimpleLangParser.ID, 0); }
		public FuncArgsContext funcArgs() {
			return getRuleContext(FuncArgsContext.class,0);
		}
		public TerminalNode MUL() { return getToken(SimpleLangParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(SimpleLangParser.DIV, 0); }
		public TerminalNode ADD() { return getToken(SimpleLangParser.ADD, 0); }
		public Primary_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primary_expr; }
	}

	public final Primary_exprContext primary_expr() throws RecognitionException {
		return primary_expr(0);
	}

	private Primary_exprContext primary_expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Primary_exprContext _localctx = new Primary_exprContext(_ctx, _parentState);
		Primary_exprContext _prevctx = _localctx;
		int _startState = 20;
		enterRecursionRule(_localctx, 20, RULE_primary_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(104);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				setState(91);
				match(SUB);
				setState(92);
				primary_expr(7);
				}
				break;
			case 2:
				{
				setState(93);
				match(LPAREN);
				setState(94);
				primary_expr(0);
				setState(95);
				match(RPAREN);
				}
				break;
			case 3:
				{
				setState(97);
				match(INT);
				}
				break;
			case 4:
				{
				setState(98);
				match(ID);
				}
				break;
			case 5:
				{
				setState(99);
				match(ID);
				setState(100);
				match(LPAREN);
				setState(101);
				funcArgs();
				setState(102);
				match(RPAREN);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(114);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(112);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
					case 1:
						{
						_localctx = new Primary_exprContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_primary_expr);
						setState(106);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(107);
						_la = _input.LA(1);
						if ( !(_la==MUL || _la==DIV) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(108);
						primary_expr(7);
						}
						break;
					case 2:
						{
						_localctx = new Primary_exprContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_primary_expr);
						setState(109);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(110);
						_la = _input.LA(1);
						if ( !(_la==SUB || _la==ADD) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(111);
						primary_expr(6);
						}
						break;
					}
					} 
				}
				setState(116);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Cond_exprContext extends ParserRuleContext {
		public List<TerminalNode> ID() { return getTokens(SimpleLangParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(SimpleLangParser.ID, i);
		}
		public TerminalNode LESS() { return getToken(SimpleLangParser.LESS, 0); }
		public Cond_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cond_expr; }
	}

	public final Cond_exprContext cond_expr() throws RecognitionException {
		Cond_exprContext _localctx = new Cond_exprContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_cond_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(117);
			match(ID);
			setState(118);
			match(LESS);
			setState(119);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 10:
			return primary_expr_sempred((Primary_exprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean primary_expr_sempred(Primary_exprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 6);
		case 1:
			return precpred(_ctx, 5);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u0013z\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0001"+
		"\u0000\u0004\u0000\u001a\b\u0000\u000b\u0000\f\u0000\u001b\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0003\u0005\u0003/\b\u0003"+
		"\n\u0003\f\u00032\t\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005"+
		"\u0001\u0006\u0005\u00069\b\u0006\n\u0006\f\u0006<\t\u0006\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0003\u0007M\b\u0007\u0001\b\u0001\b\u0001\b"+
		"\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0003\ni\b\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\n\u0001\n\u0001\n\u0005\nq\b\n\n\n\f\nt\t\n\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0000\u0001\u0014\f\u0000"+
		"\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0000\u0002\u0002"+
		"\u0000\t\t\u000b\u000b\u0002\u0000\b\b\n\ny\u0000\u0019\u0001\u0000\u0000"+
		"\u0000\u0002\u001d\u0001\u0000\u0000\u0000\u0004+\u0001\u0000\u0000\u0000"+
		"\u00060\u0001\u0000\u0000\u0000\b3\u0001\u0000\u0000\u0000\n5\u0001\u0000"+
		"\u0000\u0000\f:\u0001\u0000\u0000\u0000\u000eL\u0001\u0000\u0000\u0000"+
		"\u0010N\u0001\u0000\u0000\u0000\u0012T\u0001\u0000\u0000\u0000\u0014h"+
		"\u0001\u0000\u0000\u0000\u0016u\u0001\u0000\u0000\u0000\u0018\u001a\u0003"+
		"\u0002\u0001\u0000\u0019\u0018\u0001\u0000\u0000\u0000\u001a\u001b\u0001"+
		"\u0000\u0000\u0000\u001b\u0019\u0001\u0000\u0000\u0000\u001b\u001c\u0001"+
		"\u0000\u0000\u0000\u001c\u0001\u0001\u0000\u0000\u0000\u001d\u001e\u0005"+
		"\u0002\u0000\u0000\u001e\u001f\u0003\u0004\u0002\u0000\u001f \u0005\u0005"+
		"\u0000\u0000 !\u0003\u0006\u0003\u0000!\"\u0005\u0006\u0000\u0000\"#\u0005"+
		"\u0001\u0000\u0000#$\u0003\b\u0004\u0000$%\u0005\u0003\u0000\u0000%&\u0003"+
		"\n\u0005\u0000&\'\u0005\u0010\u0000\u0000\'(\u0005\u0011\u0000\u0000("+
		")\u0005\u000f\u0000\u0000)*\u0005\u0004\u0000\u0000*\u0003\u0001\u0000"+
		"\u0000\u0000+,\u0005\u0011\u0000\u0000,\u0005\u0001\u0000\u0000\u0000"+
		"-/\u0005\u0011\u0000\u0000.-\u0001\u0000\u0000\u0000/2\u0001\u0000\u0000"+
		"\u00000.\u0001\u0000\u0000\u000001\u0001\u0000\u0000\u00001\u0007\u0001"+
		"\u0000\u0000\u000020\u0001\u0000\u0000\u000034\u0005\u0011\u0000\u0000"+
		"4\t\u0001\u0000\u0000\u000056\u0003\f\u0006\u00006\u000b\u0001\u0000\u0000"+
		"\u000079\u0003\u000e\u0007\u000087\u0001\u0000\u0000\u00009<\u0001\u0000"+
		"\u0000\u0000:8\u0001\u0000\u0000\u0000:;\u0001\u0000\u0000\u0000;\r\u0001"+
		"\u0000\u0000\u0000<:\u0001\u0000\u0000\u0000=M\u0003\u0010\b\u0000>?\u0005"+
		"\u0011\u0000\u0000?@\u0005\f\u0000\u0000@A\u0003\u0014\n\u0000AB\u0005"+
		"\u000f\u0000\u0000BM\u0001\u0000\u0000\u0000CM\u0003\u0012\t\u0000DE\u0005"+
		"\u0007\u0000\u0000EF\u0005\u0005\u0000\u0000FG\u0003\u0016\u000b\u0000"+
		"GH\u0005\u0006\u0000\u0000HI\u0005\u0003\u0000\u0000IJ\u0003\f\u0006\u0000"+
		"JK\u0005\u0004\u0000\u0000KM\u0001\u0000\u0000\u0000L=\u0001\u0000\u0000"+
		"\u0000L>\u0001\u0000\u0000\u0000LC\u0001\u0000\u0000\u0000LD\u0001\u0000"+
		"\u0000\u0000M\u000f\u0001\u0000\u0000\u0000NO\u0005\u000e\u0000\u0000"+
		"OP\u0005\u0011\u0000\u0000PQ\u0005\f\u0000\u0000QR\u0003\u0014\n\u0000"+
		"RS\u0005\u000f\u0000\u0000S\u0011\u0001\u0000\u0000\u0000TU\u0005\u0011"+
		"\u0000\u0000UV\u0005\u0005\u0000\u0000VW\u0003\u0006\u0003\u0000WX\u0005"+
		"\u0006\u0000\u0000XY\u0005\u000f\u0000\u0000Y\u0013\u0001\u0000\u0000"+
		"\u0000Z[\u0006\n\uffff\uffff\u0000[\\\u0005\b\u0000\u0000\\i\u0003\u0014"+
		"\n\u0007]^\u0005\u0005\u0000\u0000^_\u0003\u0014\n\u0000_`\u0005\u0006"+
		"\u0000\u0000`i\u0001\u0000\u0000\u0000ai\u0005\u0012\u0000\u0000bi\u0005"+
		"\u0011\u0000\u0000cd\u0005\u0011\u0000\u0000de\u0005\u0005\u0000\u0000"+
		"ef\u0003\u0006\u0003\u0000fg\u0005\u0006\u0000\u0000gi\u0001\u0000\u0000"+
		"\u0000hZ\u0001\u0000\u0000\u0000h]\u0001\u0000\u0000\u0000ha\u0001\u0000"+
		"\u0000\u0000hb\u0001\u0000\u0000\u0000hc\u0001\u0000\u0000\u0000ir\u0001"+
		"\u0000\u0000\u0000jk\n\u0006\u0000\u0000kl\u0007\u0000\u0000\u0000lq\u0003"+
		"\u0014\n\u0007mn\n\u0005\u0000\u0000no\u0007\u0001\u0000\u0000oq\u0003"+
		"\u0014\n\u0006pj\u0001\u0000\u0000\u0000pm\u0001\u0000\u0000\u0000qt\u0001"+
		"\u0000\u0000\u0000rp\u0001\u0000\u0000\u0000rs\u0001\u0000\u0000\u0000"+
		"s\u0015\u0001\u0000\u0000\u0000tr\u0001\u0000\u0000\u0000uv\u0005\u0011"+
		"\u0000\u0000vw\u0005\r\u0000\u0000wx\u0005\u0011\u0000\u0000x\u0017\u0001"+
		"\u0000\u0000\u0000\u0007\u001b0:Lhpr";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}