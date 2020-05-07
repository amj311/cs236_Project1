#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"
#include <cctype>

class Tokenizer
{
public:
	Tokenizer() {};
	Tokenizer(string& input);
	Token getNextToken();
private:
	string input;
	string tokenValue = "";
	int lineCtr = 1;

	void pushChar();
	void skipChar();
	Token handleFoundTokenOfType(TOKEN_TYPE type);





	// AUTOMATA
	Token state_0();

	// Special Characters
	Token try_COLON();

	// Keywords
	Token try_QUERIES();
	Token try_RULES();
	Token try_ID();
};

#endif