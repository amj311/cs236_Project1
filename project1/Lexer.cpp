#include "Lexer.h"

Lexer::Lexer(string& input)
{
	this->input = input;
	tokenizer = Tokenizer(input);
}

void Lexer::tokenizeInput()
{
	addToken();
}
