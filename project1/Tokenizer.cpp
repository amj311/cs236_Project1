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

string Tokenizer::advanceChar()
{
	tokenValue += input[0];
	input = input.substr(1, input.size()-1);
	cout << input.substr(0, 5) << endl;
	return input;
}

Token Tokenizer::handleFoundTokenOfType(TOKEN_TYPE type)
{
	return Token(type, tokenValue, linePos);
}

Token Tokenizer::state_0()
{
	switch (input.front())
	{
	case 'Q': return try_Queries();
	default:
		break;
	}
}


// KEYWORDS

Token Tokenizer::try_Queries()
{
	if (input.front() != 'Q') throw exception("Arrived at try_Queries but char was not Q!");
	else advanceChar();

	if (input.front() == 'u') advanceChar();
	else return try_ID();

	if (input.front() == 'e') advanceChar();
	else return try_ID();

	if (input.front() == 'r') advanceChar();
	else return try_ID();

	if (input.front() == 'i') advanceChar();
	else return try_ID();

	if (input.front() == 'e') advanceChar();
	else return try_ID();

	if (input.front() == 's') {
		advanceChar();
		return handleFoundTokenOfType(QUERIES);
	}
	else return try_ID();
}

Token Tokenizer::try_ID()
{
	return Token(ID,"This is a false return",500);
}
