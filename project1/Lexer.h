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

	void addToken() {
		tokens.push_back(tokenizer.getNextToken());
		cout << "Added a new Token." << endl;
		printTokens();
	}

	void printTokens() {
		for (size_t i = 0; i < tokens.size(); i++) {
			cout << "Tokens:" << endl << tokens[i].toString() << endl;
		}
	}
};

#endif
