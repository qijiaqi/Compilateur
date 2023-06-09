// Generated from /home/ktabakh/Documents/4IF/PLD-Compilateur/pld-comp/compiler/ifcc.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, TYPE=9, 
		INT=10, CHAR=11, IF=12, ELSE=13, WHILE=14, RETURN=15, CONST=16, OPM=17, 
		OPP=18, CMPOP=19, COMMENT=20, DIRECTIVE=21, WS=22, VAR=23;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "TYPE", 
			"INT", "CHAR", "IF", "ELSE", "WHILE", "RETURN", "CONST", "OPM", "OPP", 
			"CMPOP", "COMMENT", "DIRECTIVE", "WS", "VAR"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "';'", "'}'", "'='", "','", null, 
			"'int'", "'char'", "'if'", "'else'", "'while'", "'return'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, "TYPE", "INT", 
			"CHAR", "IF", "ELSE", "WHILE", "RETURN", "CONST", "OPM", "OPP", "CMPOP", 
			"COMMENT", "DIRECTIVE", "WS", "VAR"
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


	public ifccLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\31\u009c\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\3\2"+
		"\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3"+
		"\t\3\n\3\n\5\nG\n\n\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3"+
		"\r\3\16\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\17\3\17\3\20\3\20\3"+
		"\20\3\20\3\20\3\20\3\20\3\21\6\21h\n\21\r\21\16\21i\3\22\3\22\3\23\3\23"+
		"\3\24\3\24\3\24\3\24\3\24\3\24\3\24\3\24\3\24\5\24y\n\24\3\25\3\25\3\25"+
		"\3\25\7\25\177\n\25\f\25\16\25\u0082\13\25\3\25\3\25\3\25\3\25\3\25\3"+
		"\26\3\26\7\26\u008b\n\26\f\26\16\26\u008e\13\26\3\26\3\26\3\26\3\26\3"+
		"\27\3\27\3\27\3\27\3\30\6\30\u0099\n\30\r\30\16\30\u009a\4\u0080\u008c"+
		"\2\31\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35"+
		"\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\3\2\b\3\2\62;\4\2,,\61\61\4"+
		"\2--//\4\2>>@@\5\2\13\f\17\17\"\"\4\2C\\c|\2\u00a4\2\3\3\2\2\2\2\5\3\2"+
		"\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21"+
		"\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2"+
		"\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3"+
		"\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\3\61\3\2\2\2\5\66\3"+
		"\2\2\2\78\3\2\2\2\t:\3\2\2\2\13<\3\2\2\2\r>\3\2\2\2\17@\3\2\2\2\21B\3"+
		"\2\2\2\23F\3\2\2\2\25H\3\2\2\2\27L\3\2\2\2\31Q\3\2\2\2\33T\3\2\2\2\35"+
		"Y\3\2\2\2\37_\3\2\2\2!g\3\2\2\2#k\3\2\2\2%m\3\2\2\2\'x\3\2\2\2)z\3\2\2"+
		"\2+\u0088\3\2\2\2-\u0093\3\2\2\2/\u0098\3\2\2\2\61\62\7o\2\2\62\63\7c"+
		"\2\2\63\64\7k\2\2\64\65\7p\2\2\65\4\3\2\2\2\66\67\7*\2\2\67\6\3\2\2\2"+
		"89\7+\2\29\b\3\2\2\2:;\7}\2\2;\n\3\2\2\2<=\7=\2\2=\f\3\2\2\2>?\7\177\2"+
		"\2?\16\3\2\2\2@A\7?\2\2A\20\3\2\2\2BC\7.\2\2C\22\3\2\2\2DG\5\25\13\2E"+
		"G\5\27\f\2FD\3\2\2\2FE\3\2\2\2G\24\3\2\2\2HI\7k\2\2IJ\7p\2\2JK\7v\2\2"+
		"K\26\3\2\2\2LM\7e\2\2MN\7j\2\2NO\7c\2\2OP\7t\2\2P\30\3\2\2\2QR\7k\2\2"+
		"RS\7h\2\2S\32\3\2\2\2TU\7g\2\2UV\7n\2\2VW\7u\2\2WX\7g\2\2X\34\3\2\2\2"+
		"YZ\7y\2\2Z[\7j\2\2[\\\7k\2\2\\]\7n\2\2]^\7g\2\2^\36\3\2\2\2_`\7t\2\2`"+
		"a\7g\2\2ab\7v\2\2bc\7w\2\2cd\7t\2\2de\7p\2\2e \3\2\2\2fh\t\2\2\2gf\3\2"+
		"\2\2hi\3\2\2\2ig\3\2\2\2ij\3\2\2\2j\"\3\2\2\2kl\t\3\2\2l$\3\2\2\2mn\t"+
		"\4\2\2n&\3\2\2\2op\7?\2\2py\7?\2\2qr\7#\2\2ry\7?\2\2sy\t\5\2\2tu\7>\2"+
		"\2uy\7?\2\2vw\7@\2\2wy\7?\2\2xo\3\2\2\2xq\3\2\2\2xs\3\2\2\2xt\3\2\2\2"+
		"xv\3\2\2\2y(\3\2\2\2z{\7\61\2\2{|\7,\2\2|\u0080\3\2\2\2}\177\13\2\2\2"+
		"~}\3\2\2\2\177\u0082\3\2\2\2\u0080\u0081\3\2\2\2\u0080~\3\2\2\2\u0081"+
		"\u0083\3\2\2\2\u0082\u0080\3\2\2\2\u0083\u0084\7,\2\2\u0084\u0085\7\61"+
		"\2\2\u0085\u0086\3\2\2\2\u0086\u0087\b\25\2\2\u0087*\3\2\2\2\u0088\u008c"+
		"\7%\2\2\u0089\u008b\13\2\2\2\u008a\u0089\3\2\2\2\u008b\u008e\3\2\2\2\u008c"+
		"\u008d\3\2\2\2\u008c\u008a\3\2\2\2\u008d\u008f\3\2\2\2\u008e\u008c\3\2"+
		"\2\2\u008f\u0090\7\f\2\2\u0090\u0091\3\2\2\2\u0091\u0092\b\26\2\2\u0092"+
		",\3\2\2\2\u0093\u0094\t\6\2\2\u0094\u0095\3\2\2\2\u0095\u0096\b\27\3\2"+
		"\u0096.\3\2\2\2\u0097\u0099\t\7\2\2\u0098\u0097\3\2\2\2\u0099\u009a\3"+
		"\2\2\2\u009a\u0098\3\2\2\2\u009a\u009b\3\2\2\2\u009b\60\3\2\2\2\t\2Fi"+
		"x\u0080\u008c\u009a\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}