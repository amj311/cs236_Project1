#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
//#include "Tokenizer.h"
#include "Token.h"
#include "Automaton.h"
#include "FSA_COMMA.h"
using namespace std;

class Lexer
{
public:
	Lexer(string& input); 
	void tokenizeInput();
	vector<Token> getTokenList();
	void printTokens();

private:
	string input;
	int lineNumber = 1;
	//Tokenizer tokenizer;
	vector<Automaton*> machines = {
		new FSA_COMMA(),
	/*
		COMMA,
		PERIOD,
		Q_MARK,
		LEFT_PAREN,
		RIGHT_PAREN,
		COLON,
		COLON_DASH,
		MULTIPLY,
		ADD,
		STRING,
		COMMENT,
		SCHEMES,
		FACTS,
		RULES,
		QUERIES,
		ID,
	*/
	};
	vector<Token> tokens;

	Token findNextToken();
	void checkWhiteSpace();
};

#endif
