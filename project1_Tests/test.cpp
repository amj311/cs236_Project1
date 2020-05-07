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
TEST(TokenTest, toString) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.toString(), "(COMMA,\";\",5)");
}


TEST(TokenizerTest, EmptyInput) {
	string test = "";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(EOF,\"\",1)");
}
TEST(TokenizerTest, EmptyLine) {
	string test = "\n";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(EOF,\"\",1)");
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
TEST(TokenizerTest, FactsSpace) {
	string test = "Facts ";
	Tokenizer tokenizer(test);
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(FACTS,\"Facts\",1)");
}
TEST(TokenizerTest, FactsSEnd) {
	string test = "Factss";
	Tokenizer tokenizer(test);
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(ID,\"Factss\",1)");
}
TEST(TokenizerTest, SchemSpace) {
	string test = "Schem ";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(ID,\"Schem\",1)");
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

TEST(TokenizerTest, _GoodString_) {
	string test = " 'This is a string.' ";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(STRING,\"'This is a string.'\",1)");
}
TEST(TokenizerTest, _OpenMultilineString_) {
	string test = " 'This is a\nbad string.\n\n";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(UNDEFINED,\"'This is a\nbad string.\n\n\",1)");
}


TEST(TokenizerTest, GoodMultilineComment) {
	string test = "\n#|comment >= \nwow|#\n";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(COMMENT,\"#|comment >= \nwow|#\",2)");
}
TEST(TokenizerTest, BadMultilineComment_EOF) {
	string test = "\n#|comment >= \nwow| \n";
	Tokenizer tokenizer(test);
	string res1 = tokenizer.getNextToken().toString();
	EXPECT_EQ(res1, "(UNDEFINED,\"#|comment >= \nwow| \n\",2)");
}
TEST(TokenizerTest, GoodInlineComment) {
	string test = "\nQueries #comment >= wow| \n";
	Tokenizer tokenizer(test);
	tokenizer.getNextToken();
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(COMMENT,\"#comment >= wow| \",2)");
}
TEST(TokenizerTest, BadInlineComment) {
	string test = "\nQueries #comment \n>= wow| \n";
	Tokenizer tokenizer(test);
	tokenizer.getNextToken();
	string res = tokenizer.getNextToken().toString();
	EXPECT_EQ(res, "(COMMENT,\"#comment \",2)");
}



