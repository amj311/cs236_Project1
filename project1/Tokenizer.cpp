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

Token Tokenizer::handleFoundTokenOfType(TOKEN_TYPE type, bool shouldPush = true)
{
	if (shouldPush) pushChar();
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
		case ',': return try_COMMA();
		case '.': return try_PERIOD();
		case '?': return try_Q_MARK();
		case '(': return try_LEFT_PAREN();
		case ')': return try_RIGHT_PAREN();
		case ':': return try_COLON();
		case '*': return try_MULTIPLY();
		case '+': return try_ADD();
		// Keywords
		case 'S': return try_SCHEMES();
		case 'F': return try_FACTS();
		case 'Q': return try_QUERIES();
		case 'R': return try_RULES();
		default:
			break;
	}
}



// SPECIAL CHARACTERS

Token Tokenizer::try_COMMA()
{
	if (input.front() != ',') throw exception("Arrived at try_COMMA but char is not ','!");
	else return handleFoundTokenOfType(COMMA);
}

Token Tokenizer::try_PERIOD()
{
	if (input.front() != '.') throw exception("Arrived at try_PERIOD but char is not '.'!");
	else return handleFoundTokenOfType(PERIOD);
}

Token Tokenizer::try_Q_MARK()
{
	if (input.front() != '?') throw exception("Arrived at try_Q_MARK but char is not '?'!");
	else return handleFoundTokenOfType(Q_MARK);
}

Token Tokenizer::try_LEFT_PAREN()
{
	if (input.front() != '(') throw exception("Arrived at try_LEFT_PAREN but char is not '('!");
	else return handleFoundTokenOfType(LEFT_PAREN);
}

Token Tokenizer::try_RIGHT_PAREN()
{
	if (input.front() != ')') throw exception("Arrived at try_RIGHT_PAREN but char is not ')'!");
	else return handleFoundTokenOfType(RIGHT_PAREN);
}

Token Tokenizer::try_COLON()
{
	if (input.front() != ':') throw exception("Arrived at try_COLON but char is not ':'!");
	if (input[1] == '-') {
		pushChar();
		return handleFoundTokenOfType(COLON_DASH);
	}
	else return handleFoundTokenOfType(COLON);
}

Token Tokenizer::try_MULTIPLY()
{
	if (input.front() != '*') throw exception("Arrived at try_MULTIPLY but char is not '*'!");
	else return handleFoundTokenOfType(MULTIPLY);
}

Token Tokenizer::try_ADD()
{
	if (input.front() != '+') throw exception("Arrived at try_ADD but char is not '+'!");
	else return handleFoundTokenOfType(ADD);
}




// KEYWORDS

Token Tokenizer::try_SCHEMES()
{
	if (input.front() != 'S') throw exception("Arrived at try_SCHEMES but char was not 'S'!");
	else pushChar();

	if (input.front() == 'c') pushChar();
	else return try_ID();

	if (input.front() == 'h') pushChar();
	else return try_ID();

	if (input.front() == 'e') pushChar();
	else return try_ID();

	if (input.front() == 'm') pushChar();
	else return try_ID();

	if (input.front() == 'e') pushChar();
	else return try_ID();

	if (input.front() == 's') {
		return handleFoundTokenOfType(SCHEMES);
	}
	else return try_ID();
}

Token Tokenizer::try_FACTS()
{
	if (input.front() != 'F') throw exception("Arrived at try_FACTS but char was not 'F'!");
	else pushChar();

	if (input.front() == 'a') pushChar();
	else return try_ID();

	if (input.front() == 'c') pushChar();
	else return try_ID();

	if (input.front() == 't') pushChar();
	else return try_ID();

	if (input.front() == 's') {
		return handleFoundTokenOfType(FACTS);
	}
	else return try_ID();
}

Token Tokenizer::try_QUERIES()
{
	if (input.front() != 'Q') throw exception("Arrived at try_QUERIES but char was not 'Q'!");
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

Token Tokenizer::try_RULES()
{
	if (input.front() != 'R') throw exception("Arrived at try_RULES but char was not 'R'!");
	else pushChar();

	if (input.front() == 'u') pushChar();
	else return try_ID();

	if (input.front() == 'l') pushChar();
	else return try_ID();

	if (input.front() == 'e') pushChar();
	else return try_ID();

	if (input.front() == 's') {
		return handleFoundTokenOfType(RULES);
	}
	else return try_ID();
}

Token Tokenizer::try_ID()
{
	if (isspace(input.front())) return handleFoundTokenOfType(ID, false);
	return Token(ID,"This is a false return",500);
}
