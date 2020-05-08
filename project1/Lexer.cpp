#include "Lexer.h"

Lexer::Lexer(string& input)
{
	this->input = input;
	tokenizer = Tokenizer(input);
}

void Lexer::tokenizeInput()
{
	do {
		addToken();
	} while (tokens.back().getType() != EOF_TYPE);
	printTokens();
}

vector<Token> Lexer::getTokenList()
{
	return tokens;
}

void Lexer::addToken()
{
	tokens.push_back(tokenizer.getNextToken());
}

void Lexer::printTokens()
{
	for (size_t i = 0; i < tokens.size(); i++) {
		cout << tokens[i].toString() << endl;
	}
	cout << "Total Tokens = " << tokens.size() << endl;
}
