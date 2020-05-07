#include "Token.h"

Token::Token(TOKEN_TYPE type, string value, int line)
{
	this->type = type;
	this->value = value;
	this->line = line;
}

TOKEN_TYPE Token::getType()
{
	return type;
}

string Token::getValue()
{
	return value;
}

int Token::getLine()
{
	return line;
}

string Token::toString()
{
	return "(" + TOKEN_STRINGS[type] + ",\"" + value + "\"," + to_string(line) + ")";
}
