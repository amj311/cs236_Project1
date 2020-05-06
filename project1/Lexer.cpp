#include "Lexer.h"

Lexer::Lexer(string& input)
{
	this->input = input;
	cout << "Made a new Lexer with input: " << this->input << endl;
}
