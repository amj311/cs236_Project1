#include "pch.h"
#include "../project1/Lexer.h"


TEST(TokenTypesTest, TypeStringsDef) {
	string comma = TOKEN_TYPE_STRINGS[COMMA];
	EXPECT_EQ(comma, "COMMA");
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
TEST(TokenTest, Print) {
	Token token(COMMA, ";", 5);
	EXPECT_EQ(token.toString(), "(COMMA,\";\",5)");
}


