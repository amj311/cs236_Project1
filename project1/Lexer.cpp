#include "Lexer.h"

Lexer::Lexer(string& input)
{
	this->input = input;
}

void Lexer::tokenizeInput()
{
	lineNumber = 1;
	tokens.clear();

	do {
		tokens.push_back(findNextToken());

	} while (tokens.back().getType() != EOF_TYPE);
	printTokens();
}

Token Lexer::findNextToken()
{
	int longestRead = 0;

	checkWhiteSpace();
	if (input.length() <= 0) return Token(EOF_TYPE, "", lineNumber);

	size_t m = 0;
	for (; m < machines.size(); m++)
	{
		int charsRead = machines[m]->Read(input);
		if (charsRead > longestRead) longestRead = charsRead;
	}

	Token token;
	if (longestRead > 0) token = Token(machines[m]->type, input.substr(longestRead), lineNumber);
	else token = Token(UNDEFINED, input.substr(1), lineNumber);

	for (size_t c = 0; c < tokens.back().getValue().length(); c++) {
		if (c == '\n') lineNumber++;
	}
	input = input.substr(longestRead);

	return token;
}

void Lexer::checkWhiteSpace() {
	while (input.length() > 0 && isspace(input.front())) {
		if (input.front() == '\n') lineNumber++;
		input = input.substr(1);
	}
}

vector<Token> Lexer::getTokenList()
{
	return tokens;
}

void Lexer::printTokens()
{
	for (size_t i = 0; i < tokens.size(); i++)
	{
		cout << tokens[i].toString() << endl;
	}
	cout << "Total Tokens = " << tokens.size() << endl;
}
