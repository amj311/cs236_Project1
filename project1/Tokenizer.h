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
	int tokenLine = 1;
	int lineCtr = 1;
	
	bool isEOF();
	char curChar();
	char nextChar();
	void pushChar();
	void skipChar();
	Token handleFoundTokenOfType(TOKEN_TYPE type, bool shouldPush);





	// AUTOMATA
	Token state_0();

	// Special Characters
	Token try_COMMA();
	Token try_PERIOD();
	Token try_Q_MARK();
	Token try_LEFT_PAREN();
	Token try_RIGHT_PAREN();
	Token try_COLON();
	Token try_MULTIPLY();
	Token try_ADD();
	Token try_STRING();
	Token try_COMMENT();

	// Keywords
	Token try_SCHEMES();
	Token try_FACTS();
	Token try_QUERIES();
	Token try_RULES();
	Token try_ID();
};

#endif