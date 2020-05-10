#include "pch.h"
#include "../project1/Lexer.h"

#include <fstream>

string getFile(string path) {
	ifstream ifs(path);
	return string((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));
}

TEST(InputFile, Log) {
	string file = getFile("../project1/project1-exampleIO/in10.txt");
	cout << endl << file << endl << endl;

	EXPECT_EQ(file.length(), 89);
}



TEST(TokenTest, ConstrType) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.getType(), COMMA);
}
TEST(TokenTest, ConstrValue) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.getValue(), ";");
}
TEST(TokenTest, ConstrLine) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.getLine(), 5);
}
TEST(TokenTest, toString) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.toString(), "(COMMA,\";\",5)");
}






TEST(FSA_COMMA, Good) {
	string test = ",,";
	FSA_COMMA fsa = FSA_COMMA();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_COMMA, Bad) {
	string test = "g";
	FSA_COMMA fsa = FSA_COMMA();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_COMMA, Lexer) {
	string test = "  ,\n ,";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(COMMA,\",\",2)");
}


TEST(FSA_PERIOD, Good) {
	string test = "..";
	FSA_PERIOD fsa = FSA_PERIOD();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_PERIOD, Bad) {
	string test = "g";
	FSA_PERIOD fsa = FSA_PERIOD();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_PERIOD, Lexer) {
	string test = "  .\n .";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(PERIOD,\".\",2)");
}


TEST(FSA_Q_MARK, Good) {
	string test = "? ?";
	FSA_Q_MARK fsa = FSA_Q_MARK();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_Q_MARK, Bad) {
	string test = "g";
	FSA_Q_MARK fsa = FSA_Q_MARK();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_Q_MARK, Lexer) {
	string test = "  ?\n ?";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(Q_MARK,\"?\",2)");
}


TEST(FSA_LEFT_PAREN, Good) {
	string test = "( (";
	FSA_LEFT_PAREN fsa = FSA_LEFT_PAREN();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_LEFT_PAREN, Bad) {
	string test = "g";
	FSA_LEFT_PAREN fsa = FSA_LEFT_PAREN();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_LEFT_PAREN, Lexer) {
	string test = "  (\n (";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(LEFT_PAREN,\"(\",2)");
}


TEST(FSA_RIGHT_PAREN, Good) {
	string test = ") )";
	FSA_RIGHT_PAREN fsa = FSA_RIGHT_PAREN();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_RIGHT_PAREN, Bad) {
	string test = "g";
	FSA_RIGHT_PAREN fsa = FSA_RIGHT_PAREN();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_RIGHT_PAREN, Lexer) {
	string test = "  )\n )";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(RIGHT_PAREN,\")\",2)");
}


TEST(FSA_COLON, Good) {
	string test = ": :";
	FSA_COLON fsa = FSA_COLON();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_COLON, Bad) {
	string test = "g";
	FSA_COLON fsa = FSA_COLON();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_COLON, COLON_DASH) {
	string test = ":-";
	FSA_COLON fsa = FSA_COLON();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 2);
}
TEST(FSA_COLON, Lexer) {
	string test = "  :\n :-";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(COLON_DASH,\":-\",2)");
}


TEST(FSA_MULTIPLY, Good) {
	string test = "* *";
	FSA_MULTIPLY fsa = FSA_MULTIPLY();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_MULTIPLY, Bad) {
	string test = "g";
	FSA_MULTIPLY fsa = FSA_MULTIPLY();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_MULTIPLY, Lexer) {
	string test = "  *\n *";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(MULTIPLY,\"*\",2)");
}


TEST(FSA_ADD, Good) {
	string test = "+ +";
	FSA_ADD fsa = FSA_ADD();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_ADD, Bad) {
	string test = "g";
	FSA_ADD fsa = FSA_ADD();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_ADD, Lexer) {
	string test = "  +\n +";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(ADD,\"+\",2)");
}



TEST(FSA_SCHEMES, Good) {
	string test = "Schemes";
	FSA_SCHEMES fsa = FSA_SCHEMES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 7);
}
TEST(FSA_SCHEMES, Bad) {
	string test = "SCHEMES";
	FSA_SCHEMES fsa = FSA_SCHEMES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_SCHEMES, Lexer) {
	string test = "  Schemes\n Schemes";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(SCHEMES,\"Schemes\",2)");
}


TEST(FSA_FACTS, Good) {
	string test = "Facts";
	FSA_FACTS fsa = FSA_FACTS();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 5);
}
TEST(FSA_FACTS, Bad) {
	string test = "FACTS";
	FSA_FACTS fsa = FSA_FACTS();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_FACTS, Lexer) {
	string test = "  Facts\n Facts";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(FACTS,\"Facts\",2)");
}


TEST(FSA_RULES, Good) {
	string test = "Rules";
	FSA_RULES fsa = FSA_RULES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 5);
}
TEST(FSA_RULES, Bad) {
	string test = "RULES";
	FSA_RULES fsa = FSA_RULES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_RULES, Lexer) {
	string test = "  Rules\n Rules";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(RULES,\"Rules\",2)");
}


TEST(FSA_QUERIES, Good) {
	string test = "Queries";
	FSA_QUERIES fsa = FSA_QUERIES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 7);
}
TEST(FSA_QUERIES, Bad) {
	string test = "QUERIES";
	FSA_QUERIES fsa = FSA_QUERIES();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_QUERIES, Lexer) {
	string test = "  Queries\n Queries";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(QUERIES,\"Queries\",2)");
}





TEST(FSA_COMMENT, Good) {
	string test = "# This is a comment.";
	FSA_COMMENT fsa = FSA_COMMENT();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 20);
}
TEST(FSA_COMMENT, Bad) {
	string test = "COMMENT";
	FSA_COMMENT fsa = FSA_COMMENT();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 0);
}
TEST(FSA_COMMENT, Lexer) {
	string test = "  # This is a comment.\n # This is a comment.";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[1].toString();
	EXPECT_EQ(res, "(COMMENT,\"# This is a comment.\",2)");
}





TEST(FSA_COMMENT_LONG, Good) {
	string test = "#| This is a \n comment. |#";
	FSA_COMMENT_LONG fsa = FSA_COMMENT_LONG();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 26);
}
TEST(FSA_COMMENT_LONG, Bad) {
	string test = "# This is a \n comment. |#";
	FSA_COMMENT_LONG fsa = FSA_COMMENT_LONG();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 1);
}
TEST(FSA_COMMENT_LONG, BAD_EOF) {
	string test = "#| This is a |";
	FSA_COMMENT_LONG fsa = FSA_COMMENT_LONG();
	int res = fsa.Read(test);
	EXPECT_EQ(res, 14);
}
TEST(FSA_COMMENT_LONG, Lexer) {
	string test = "  #| This is a c #| omment.\n # This is a comment.|#";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[0].toString();
	EXPECT_EQ(res, "(COMMENT,\"#| This is a c #| omment.\n # This is a comment.|#\",1)");
}







TEST(LexerTest, EmptyInput) {
	string test = "";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[0].toString();
	EXPECT_EQ(res, "(EOF,\"\",1)");
}
TEST(LexerTest, EmptyNewline) {
	string test = "\n";
	Lexer lexer(test);
	lexer.tokenizeInput();
	vector<Token> tokens = lexer.getTokenList();
	string res = tokens[0].toString();
	EXPECT_EQ(res, "(EOF,\"\",2)");
}



TEST(LexerTest, Q_EmptyLinex2) {
	string test = "Q \n\n";
	Lexer lexer(test);
	lexer.findNextToken();
	string res = lexer.findNextToken().toString();
	EXPECT_EQ(res, "(EOF,\"\",3)");
}
//TEST(LexerTest, SpacesQueries) {
//	string test = "     Queries:";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(QUERIES,\"Queries\",1)");
//}
//TEST(LexerTest, TabsRules) {
//	string test = "\t\tRules:";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(RULES,\"Rules\",1)");
//}
//TEST(LexerTest, NewlinesQueries) {
//	string test = "\n\nQueries:";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(QUERIES,\"Queries\",3)");
//}
//TEST(LexerTest, QueriesColon1) {
//	string test = "Queries:";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(QUERIES,\"Queries\",1)");
//}
//TEST(LexerTest, QueriesColon2) {
//	string test = "Queries:";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res2 = lexer.findNextToken().toString();
//	EXPECT_EQ(res2, "(COLON,\":\",1)");
//}
//TEST(LexerTest, FactsSpace) {
//	string test = "Facts ";
//	Lexer lexer(test);
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(FACTS,\"Facts\",1)");
//}
//TEST(LexerTest, FactsSEnd) {
//	string test = "Factss";
//	Lexer lexer(test);
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(ID,\"Factss\",1)");
//}
//TEST(LexerTest, SchemSpace) {
//	string test = "Schem ";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(ID,\"Schem\",1)");
//}
//
//TEST(LexerTest, ColonDash) {
//	string test = ":-";
//	Lexer lexer(test);
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(COLON_DASH,\":-\",1)");
//}
//TEST(LexerTest, ColonDashComma) {
//	string test = ":-,";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(COMMA,\",\",1)");
//}
//TEST(LexerTest, AllSpecialCharacters) {
//	string test = ",.?()::-*+";
//	Token token(COMMA,",",5);
//	Lexer lexer(test);
//	string res = "";
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	res += token.TOKEN_STRINGS[lexer.findNextToken().getType()];
//	EXPECT_EQ(res, "COMMAPERIODQ_MARKLEFT_PARENRIGHT_PARENCOLONCOLON_DASHMULTIPLYADD");
//}
//
TEST(LexerTest, _GoodString_) {
	string test = " 'This is a string.' ";
	Lexer lexer(test);

	string res1 = lexer.findNextToken().toString();
	EXPECT_EQ(res1, "(STRING,\"'This is a string.'\",1)");
}
TEST(LexerTest, _OpenMultilineString_) {
	string test = " 'This is a\nbad string.\n\n";
	Lexer lexer(test);
	string res1 = lexer.findNextToken().toString();
	EXPECT_EQ(res1, "(UNDEFINED,\"'This is a\nbad string.\n\n\",1)");
}
//
//TEST(LexerTest, Aposx3) {
//	string test = "'''\n";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(UNDEFINED,\"'''\n\",1)");
//}
//TEST(LexerTest, EmptyString_EmptyString) {
//	string test = "'' ''\n";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(STRING,\"''\",1)");
//}
//
//
//TEST(LexerTest, GoodMultilineComment) {
//	string test = "\n#|comment >= \nwow|#\n";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(COMMENT,\"#|comment >= \nwow|#\",2)");
//}
//TEST(LexerTest, BadMultilineComment_EOF) {
//	string test = "\n#|comment >= \nwow| \n";
//	Lexer lexer(test);
//	string res1 = lexer.findNextToken().toString();
//	EXPECT_EQ(res1, "(UNDEFINED,\"#|comment >= \nwow| \n\",2)");
//}
//TEST(LexerTest, GoodInlineComment) {
//	string test = "\nQueries #comment >= wow| \n";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(COMMENT,\"#comment >= wow| \",2)");
//}
//TEST(LexerTest, BadInlineComment) {
//	string test = "\nQueries #comment \n>= wow| \n";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(COMMENT,\"#comment \",2)");
//}
//
//TEST(LexerTest, X_comma_y) {
//	string test = "X,Y";
//	Lexer lexer(test);
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(ID,\"X\",1)");
//}
//TEST(LexerTest, x_COMMA_y) {
//	string test = "X,Y";
//	Lexer lexer(test);
//	lexer.findNextToken();
//	string res = lexer.findNextToken().toString();
//	EXPECT_EQ(res, "(COMMA,\",\",1)");
//}
//
//
//
//TEST(File10, lexer) {
//	string test = getFile("../project1/project1-exampleIO/in10.txt");
//	cout << endl << test << endl;
//	Lexer lexer(test);
//	for (size_t i = 0; i < 25; i++) {
//		cout << lexer.findNextToken().toString() << endl;
//	}
//	string res = lexer.findNextToken().toString();
//	cout << res << endl;
//	EXPECT_EQ(res, "(EOF,\"\",8)");
//}
//
//TEST(File10, lexer) {
//	string test = getFile("../project1/project1-exampleIO/in10.txt");
//	cout << endl << test << endl;
//	Lexer lexer(test);
//	lexer.tokenizeInput();
//	lexer.printTokens();
//	vector<Token> list = lexer.getTokenList();
//	Token res = list[list.size() - 1];
//	EXPECT_EQ(res.toString(), "(EOF,\"\",8)");
//}
//
//
//
//TEST(File19, lexer) {
//	string test = getFile("../project1/project1-exampleIO/in19.txt");
//	cout << endl << test << endl;
//	Lexer lexer(test);
//	for (size_t i = 0; i < 22; i++) {
//		cout << lexer.findNextToken().toString() << endl;
//	}
//	string res = lexer.findNextToken().toString();
//	cout << res << endl;
//	EXPECT_EQ(res, "(UNDEFINED,\"'this has a\nReturn\nThe end''s near\n\",7)");
//}
//
//TEST(File19, lexer) {
//	string test = getFile("../project1/project1-exampleIO/in19.txt");
//	cout << endl << test << endl;
//	Lexer lexer(test);
//	lexer.tokenizeInput();
//	lexer.printTokens();
//	vector<Token> list = lexer.getTokenList();
//	Token res = list[list.size() - 2];
//	EXPECT_EQ(res.toString(), "(UNDEFINED,\"'this has a\nReturn\nThe end''s near\n\",7)");
//}
