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
	return Token(type, tokenValue, linePos);
}

Token Tokenizer::state_0()
{
	switch (input.front())
	{
	case ' ':
		skipChar();
		return state_0();
	case 'Q': return try_Queries();
	default:
		break;
	}
}


// KEYWORDS

Token Tokenizer::try_Queries()
{
	if (input.front() != 'Q') throw exception("Arrived at try_Queries but char was not Q!");
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
		pushChar();
		return handleFoundTokenOfType(QUERIES);
	}
	else return try_ID();
}

Token Tokenizer::try_ID()
{
	return Token(ID,"This is a false return",500);
}
