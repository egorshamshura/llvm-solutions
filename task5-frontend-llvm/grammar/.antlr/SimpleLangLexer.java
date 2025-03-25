// Generated from /root/llvm-solutions/solutions/task5-frontend-llvm/grammar/SimpleLangLexer.g4 by ANTLR 4.13.1
/* lexer header section */
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class SimpleLangLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ARROW=1, FUNC=2, LCBRACE=3, RCBRACE=4, LPAREN=5, RPAREN=6, WHILE=7, SUB=8, 
		MUL=9, ADD=10, DIV=11, EQ=12, LESS=13, VAR=14, SEMICOLON=15, RETURN=16, 
		ID=17, INT=18, WS=19;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"ARROW", "FUNC", "LCBRACE", "RCBRACE", "LPAREN", "RPAREN", "WHILE", "SUB", 
			"MUL", "ADD", "DIV", "EQ", "LESS", "VAR", "SEMICOLON", "RETURN", "ID", 
			"INT", "WS"
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

	/* public lexer declarations section */


	public SimpleLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "SimpleLangLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0013g\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002"+
		"\u0012\u0007\u0012\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0007\u0001\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001"+
		"\u000b\u0001\u000b\u0001\f\u0001\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\u000e\u0001\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0004\u0010X\b\u0010\u000b"+
		"\u0010\f\u0010Y\u0001\u0011\u0004\u0011]\b\u0011\u000b\u0011\f\u0011^"+
		"\u0001\u0012\u0004\u0012b\b\u0012\u000b\u0012\f\u0012c\u0001\u0012\u0001"+
		"\u0012\u0000\u0000\u0013\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004"+
		"\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017"+
		"\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\u0001"+
		"\u0000\u0003\u0003\u0000AZ__az\u0001\u000009\u0003\u0000\t\n\r\r  i\u0000"+
		"\u0001\u0001\u0000\u0000\u0000\u0000\u0003\u0001\u0000\u0000\u0000\u0000"+
		"\u0005\u0001\u0000\u0000\u0000\u0000\u0007\u0001\u0000\u0000\u0000\u0000"+
		"\t\u0001\u0000\u0000\u0000\u0000\u000b\u0001\u0000\u0000\u0000\u0000\r"+
		"\u0001\u0000\u0000\u0000\u0000\u000f\u0001\u0000\u0000\u0000\u0000\u0011"+
		"\u0001\u0000\u0000\u0000\u0000\u0013\u0001\u0000\u0000\u0000\u0000\u0015"+
		"\u0001\u0000\u0000\u0000\u0000\u0017\u0001\u0000\u0000\u0000\u0000\u0019"+
		"\u0001\u0000\u0000\u0000\u0000\u001b\u0001\u0000\u0000\u0000\u0000\u001d"+
		"\u0001\u0000\u0000\u0000\u0000\u001f\u0001\u0000\u0000\u0000\u0000!\u0001"+
		"\u0000\u0000\u0000\u0000#\u0001\u0000\u0000\u0000\u0000%\u0001\u0000\u0000"+
		"\u0000\u0001\'\u0001\u0000\u0000\u0000\u0003*\u0001\u0000\u0000\u0000"+
		"\u0005/\u0001\u0000\u0000\u0000\u00071\u0001\u0000\u0000\u0000\t3\u0001"+
		"\u0000\u0000\u0000\u000b5\u0001\u0000\u0000\u0000\r7\u0001\u0000\u0000"+
		"\u0000\u000f=\u0001\u0000\u0000\u0000\u0011?\u0001\u0000\u0000\u0000\u0013"+
		"A\u0001\u0000\u0000\u0000\u0015C\u0001\u0000\u0000\u0000\u0017E\u0001"+
		"\u0000\u0000\u0000\u0019G\u0001\u0000\u0000\u0000\u001bI\u0001\u0000\u0000"+
		"\u0000\u001dM\u0001\u0000\u0000\u0000\u001fO\u0001\u0000\u0000\u0000!"+
		"W\u0001\u0000\u0000\u0000#\\\u0001\u0000\u0000\u0000%a\u0001\u0000\u0000"+
		"\u0000\'(\u0005-\u0000\u0000()\u0005>\u0000\u0000)\u0002\u0001\u0000\u0000"+
		"\u0000*+\u0005f\u0000\u0000+,\u0005u\u0000\u0000,-\u0005n\u0000\u0000"+
		"-.\u0005c\u0000\u0000.\u0004\u0001\u0000\u0000\u0000/0\u0005{\u0000\u0000"+
		"0\u0006\u0001\u0000\u0000\u000012\u0005}\u0000\u00002\b\u0001\u0000\u0000"+
		"\u000034\u0005(\u0000\u00004\n\u0001\u0000\u0000\u000056\u0005)\u0000"+
		"\u00006\f\u0001\u0000\u0000\u000078\u0005w\u0000\u000089\u0005h\u0000"+
		"\u00009:\u0005i\u0000\u0000:;\u0005l\u0000\u0000;<\u0005e\u0000\u0000"+
		"<\u000e\u0001\u0000\u0000\u0000=>\u0005-\u0000\u0000>\u0010\u0001\u0000"+
		"\u0000\u0000?@\u0005*\u0000\u0000@\u0012\u0001\u0000\u0000\u0000AB\u0005"+
		"+\u0000\u0000B\u0014\u0001\u0000\u0000\u0000CD\u0005/\u0000\u0000D\u0016"+
		"\u0001\u0000\u0000\u0000EF\u0005=\u0000\u0000F\u0018\u0001\u0000\u0000"+
		"\u0000GH\u0005<\u0000\u0000H\u001a\u0001\u0000\u0000\u0000IJ\u0005v\u0000"+
		"\u0000JK\u0005a\u0000\u0000KL\u0005r\u0000\u0000L\u001c\u0001\u0000\u0000"+
		"\u0000MN\u0005;\u0000\u0000N\u001e\u0001\u0000\u0000\u0000OP\u0005r\u0000"+
		"\u0000PQ\u0005e\u0000\u0000QR\u0005t\u0000\u0000RS\u0005u\u0000\u0000"+
		"ST\u0005r\u0000\u0000TU\u0005n\u0000\u0000U \u0001\u0000\u0000\u0000V"+
		"X\u0007\u0000\u0000\u0000WV\u0001\u0000\u0000\u0000XY\u0001\u0000\u0000"+
		"\u0000YW\u0001\u0000\u0000\u0000YZ\u0001\u0000\u0000\u0000Z\"\u0001\u0000"+
		"\u0000\u0000[]\u0007\u0001\u0000\u0000\\[\u0001\u0000\u0000\u0000]^\u0001"+
		"\u0000\u0000\u0000^\\\u0001\u0000\u0000\u0000^_\u0001\u0000\u0000\u0000"+
		"_$\u0001\u0000\u0000\u0000`b\u0007\u0002\u0000\u0000a`\u0001\u0000\u0000"+
		"\u0000bc\u0001\u0000\u0000\u0000ca\u0001\u0000\u0000\u0000cd\u0001\u0000"+
		"\u0000\u0000de\u0001\u0000\u0000\u0000ef\u0006\u0012\u0000\u0000f&\u0001"+
		"\u0000\u0000\u0000\u0004\u0000Y^c\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}