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
	size_t idx = 0;
};

#endif