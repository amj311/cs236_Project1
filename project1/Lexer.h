#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include "Tokenizer.h"
#include <vector>
using namespace std;

class Lexer
{
public:
	Lexer(string& input); 
	void tokenizeInput();
private:
	string input;
	Tokenizer tokenizer;
	vector<Token> tokens;

	void addToken();

	void printTokens();
};

#endif
