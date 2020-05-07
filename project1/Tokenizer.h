#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"

class Tokenizer
{
public:
	Tokenizer() {};
	Tokenizer(string& input);
	Token getNextToken();
private:
	string input;
	string tokenValue = "";
	int linePos = 1;

	string advanceChar();
	Token handleFoundTokenOfType(TOKEN_TYPE type);

	// AUTOMATA
	Token state_0();
	Token try_Queries();
	Token try_ID();
};

#endif