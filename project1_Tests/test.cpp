#include "pch.h"
#include "../project1/Lexer.h"


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
TEST(TokenTest, Print) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.toString(), "(COMMA,\";\",5)");
}


TEST(TokenizerTest, SpacesQueries) {
	string test = "     Queries:";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(QUERIES,\"Queries\",1)");
}
TEST(TokenizerTest, TabsRules) {
	string test = "\t\tRules:";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(RULES,\"Rules\",1)");
}
TEST(TokenizerTest, NewlinesQueries) {
	string test = "\n\nQueries:";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(QUERIES,\"Queries\",3)");
}
TEST(TokenizerTest, QueriesColon1) {
	string test = "Queries:";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(QUERIES,\"Queries\",1)");
}
TEST(TokenizerTest, QueriesColon2) {
	string test = "Queries:";
	Tokenizer tokenizer(test);
	tokenizer.getNextToken();
	string res2 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res2, "(COLON,\":\",1)");
}
TEST(TokenizerTest, ColonDash) {
	string test = ":-";
	Tokenizer tokenizer(test);
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(COLON_DASH,\":-\",1)");
}
TEST(TokenizerTest, ColonDashComma) {
	string test = ":-,";
	Tokenizer tokenizer(test);
	tokenizer.getNextToken();
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(COMMA,\",\",1)");
}
TEST(TokenizerTest, AllSpecialCharacters) {

	std::string TYPE_STRINGS[] = {
		"COMMA",
		"PERIOD",
		"Q_MARK",
		"LEFT_PAREN",
		"RIGHT_PAREN",
		"COLON",
		"COLON_DASH",
		"MULTIPLY",
		"ADD",
		"SCHEMES",
		"FACTS",
		"RULES",
		"QUERIES",
		"ID",
		"STRING",
		"COMMENT",
		"UNDEFINED",
		"EOF_TYPE"
	};

	string test = ",.?()::-*+";
	Tokenizer tokenizer(test);
	string res = "";
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	res += TYPE_STRINGS[tokenizer.getNextToken().getType()];
	EXPECT_EQ(res, "COMMAPERIODQ_MARKLEFT_PARENRIGHT_PARENCOLONCOLON_DASHMULTIPLYADD");
}


