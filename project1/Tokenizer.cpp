#include "Tokenizer.h"

Tokenizer::Tokenizer(string& input)
{
	this->input = input;
}

Token Tokenizer::getNextToken()
{
	tokenValue = "";
	return state_0();
}

void Tokenizer::pushChar()
{
	tokenValue += input[0];
	skipChar();
}

void Tokenizer::skipChar()
{
	input = input.substr(1, input.size() - 1);
}

Token Tokenizer::handleFoundTokenOfType(TOKEN_TYPE type)
{
	pushChar();
	return Token(type, tokenValue, lineCtr);
}

Token Tokenizer::state_0()
{
	// Whitespaces
	if (isspace(input.front())) {
		if (input.front() == '\n') lineCtr++;
		skipChar();
		return state_0();
	}
	switch (input.front())
	{
	// Special Characters
	case ':':
		return try_COLON();
	// Keywords
	case 'Q': return try_QUERIES();
	default:
		break;
	}
}

Token Tokenizer::try_COLON()
{
	if (input.front() != ':') throw exception("Arrived at try_COLON but char is not ':'!");
	else return handleFoundTokenOfType(COLON);
}


// KEYWORDS
Token Tokenizer::try_QUERIES()
{
	if (input.front() != 'Q') throw exception("Arrived at try_QUERIES but char was not Q!");
	else pushChar();

	if (input.front() == 'u') pushChar();
	else return try_ID();

	if (input.front() == 'e') pushChar();
	else return try_ID();

	if (input.front() == 'r') pushChar();
	else return try_ID();

	if (input.front() == 'i') pushChar();
	else return try_ID();

	if (input.front() == 'e') pushChar();
	else return try_ID();

	if (input.front() == 's') {
		return handleFoundTokenOfType(QUERIES);
	}
	else return try_ID();
}

Token Tokenizer::try_ID()
{
	return Token(ID,"This is a false return",500);
}
