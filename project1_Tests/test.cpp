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
	string test = ",.?()::-*+";
	Token token(COMMA,",",5);
	Tokenizer tokenizer(test);
	string res = "";
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	res += token.TOKEN_STRINGS[tokenizer.getNextToken().getType()];
	EXPECT_EQ(res, "COMMAPERIODQ_MARKLEFT_PARENRIGHT_PARENCOLONCOLON_DASHMULTIPLYADD");
}


