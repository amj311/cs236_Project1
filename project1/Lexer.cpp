#include "Lexer.h"

Lexer::Lexer(string& input)
{
	this->input = input;
	tokenizer = Tokenizer(input);
	cout << "Made a new Lexer with input: " << this->input << endl;
}

void Lexer::tokenizeInput()
{
	addToken();
}
