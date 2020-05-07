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

bool Tokenizer::isEOF()
{
	if (input.size() == 0 || (isspace(curChar()) && input.size() == 1) ) return true;
	return false;
}

char Tokenizer::curChar()
{
	return input[0];
}

char Tokenizer::nextChar()
{
	return input[1];
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
	return Token(type, tokenValue, tokenLine);
}

Token Tokenizer::state_0()
{
	// Whitespaces
	if (isEOF()) return handleFoundTokenOfType(EOF_TYPE, false);

	if (isspace(curChar())) {
		if (curChar() == '\n') lineCtr++;
		skipChar();
		return state_0();
	}

	tokenLine = lineCtr;

	switch (curChar())
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
		case '\'': return try_STRING();
		
		// Keywords
		case 'S': return try_SCHEMES();
		case 'F': return try_FACTS();
		case 'Q': return try_QUERIES();
		case 'R': return try_RULES();

		default:
			if (isalpha(curChar())) return try_ID();
			else throw exception("Invlaid starting char: " + curChar());
			break;
	}
}



// SPECIAL CHARACTERS

Token Tokenizer::try_COMMA()
{
	if (curChar() != ',') throw exception("Arrived at try_COMMA but char is not ','!");
	else return handleFoundTokenOfType(COMMA);
}

Token Tokenizer::try_PERIOD()
{
	if (curChar() != '.') throw exception("Arrived at try_PERIOD but char is not '.'!");
	else return handleFoundTokenOfType(PERIOD);
}

Token Tokenizer::try_Q_MARK()
{
	if (curChar() != '?') throw exception("Arrived at try_Q_MARK but char is not '?'!");
	else return handleFoundTokenOfType(Q_MARK);
}

Token Tokenizer::try_LEFT_PAREN()
{
	if (curChar() != '(') throw exception("Arrived at try_LEFT_PAREN but char is not '('!");
	else return handleFoundTokenOfType(LEFT_PAREN);
}

Token Tokenizer::try_RIGHT_PAREN()
{
	if (curChar() != ')') throw exception("Arrived at try_RIGHT_PAREN but char is not ')'!");
	else return handleFoundTokenOfType(RIGHT_PAREN);
}

Token Tokenizer::try_COLON()
{
	if (curChar() != ':') throw exception("Arrived at try_COLON but char is not ':'!");
	if (nextChar() == '-') {
		pushChar();
		return handleFoundTokenOfType(COLON_DASH);
	}
	else return handleFoundTokenOfType(COLON);
}

Token Tokenizer::try_MULTIPLY()
{
	if (curChar() != '*') throw exception("Arrived at try_MULTIPLY but char is not '*'!");
	else return handleFoundTokenOfType(MULTIPLY);
}

Token Tokenizer::try_ADD()
{
	if (curChar() != '+') throw exception("Arrived at try_ADD but char is not '+'!");
	else return handleFoundTokenOfType(ADD);
}

Token Tokenizer::try_STRING()
{
	//cout << "Entered try_String. Input is " + input << endl;
	if (curChar() != '\'') throw exception("Arrived at try_STRING but char is not '\''!");

	do {
		if (curChar() == '\n') lineCtr++;
		pushChar();
		//cout << "Running string: \"" << tokenValue << curChar() << "\"" << endl;
	} while ( !(curChar() == '\'' || isEOF()) );

	if (curChar() == '\'') return handleFoundTokenOfType(STRING);
	else if (isEOF()) return handleFoundTokenOfType(UNDEFINED, (curChar() == '\n'));
}




// KEYWORDS

Token Tokenizer::try_SCHEMES()
{
	if (curChar() != 'S') throw exception("Arrived at try_SCHEMES but char was not 'S'!");
	else pushChar();

	if (curChar() == 'c') pushChar();
	else return try_ID();

	if (curChar() == 'h') pushChar();
	else return try_ID();

	if (curChar() == 'e') pushChar();
	else return try_ID();

	if (curChar() == 'm') pushChar();
	else return try_ID();

	if (curChar() == 'e') pushChar();
	else return try_ID();

	if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return handleFoundTokenOfType(SCHEMES);
	else return try_ID();
}

Token Tokenizer::try_FACTS()
{
	if (curChar() != 'F') throw exception("Arrived at try_FACTS but char was not 'F'!");
	else pushChar();

	if (curChar() == 'a') pushChar();
	else return try_ID();

	if (curChar() == 'c') pushChar();
	else return try_ID();

	if (curChar() == 't') pushChar();
	else return try_ID();

	if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()) )) return handleFoundTokenOfType(FACTS);
	else return try_ID();
}

Token Tokenizer::try_QUERIES()
{
	if (curChar() != 'Q') throw exception("Arrived at try_QUERIES but char was not 'Q'!");
	else pushChar();

	if (curChar() == 'u') pushChar();
	else return try_ID();

	if (curChar() == 'e') pushChar();
	else return try_ID();

	if (curChar() == 'r') pushChar();
	else return try_ID();

	if (curChar() == 'i') pushChar();
	else return try_ID();

	if (curChar() == 'e') pushChar();
	else return try_ID();

	if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return handleFoundTokenOfType(QUERIES);
	else return try_ID();
}

Token Tokenizer::try_RULES()
{
	if (curChar() != 'R') throw exception("Arrived at try_RULES but char was not 'R'!");
	else pushChar();

	if (curChar() == 'u') pushChar();
	else return try_ID();

	if (curChar() == 'l') pushChar();
	else return try_ID();

	if (curChar() == 'e') pushChar();
	else return try_ID();

	if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return handleFoundTokenOfType(RULES);
	else return try_ID();
}

Token Tokenizer::try_ID()
{
	//cout << "Trying ID for " + tokenValue + curChar() << endl;
	
	if (isEOF() || isspace(curChar())) return handleFoundTokenOfType(ID, false);
	else {
		pushChar();
		return try_ID();
	}
}
