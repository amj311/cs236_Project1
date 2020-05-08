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
	if (isEOF()) {
		lineCtr++;
		tokenLine = lineCtr;
		return handleFoundTokenOfType(EOF_TYPE, false);
	}

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
		case '#': return try_COMMENT();
		
		// Keywords
		case 'S': return try_SCHEMES();
		case 'F': return try_FACTS();
		case 'Q': return try_QUERIES();
		case 'R': return try_RULES();

		default:
			if (isalpha(curChar())) return try_ID();
			else return handleFoundTokenOfType(UNDEFINED);
			break;
	}
}



// SPECIAL CHARACTERS

Token Tokenizer::try_COMMA()
{
	if (curChar() == ',') return handleFoundTokenOfType(COMMA);
}

Token Tokenizer::try_PERIOD()
{
	if (curChar() == '.') return handleFoundTokenOfType(PERIOD);
}

Token Tokenizer::try_Q_MARK()
{
	if (curChar() == '?') return handleFoundTokenOfType(Q_MARK);
}

Token Tokenizer::try_LEFT_PAREN()
{
	if (curChar() == '(') return handleFoundTokenOfType(LEFT_PAREN);
}

Token Tokenizer::try_RIGHT_PAREN()
{
	if (curChar() == ')') return handleFoundTokenOfType(RIGHT_PAREN);
}

Token Tokenizer::try_COLON()
{
	if (curChar() == ':') {
		if (nextChar() == '-') {
			pushChar();
			return handleFoundTokenOfType(COLON_DASH);
		}
		else return handleFoundTokenOfType(COLON);
	}
}

Token Tokenizer::try_MULTIPLY()
{
	if (curChar() == '*') return handleFoundTokenOfType(MULTIPLY);
}

Token Tokenizer::try_ADD()
{
	if (curChar() == '+') return handleFoundTokenOfType(ADD);
}

Token Tokenizer::try_STRING()
{
	//cout << "Entered try_String. Input is " + input << endl;
	if (curChar() == '\'') {
		bool stringEnd = false;

		do {
			if (curChar() == '\n') lineCtr++;
			pushChar();
			//cout << "Running string: \"" << tokenValue << curChar() << "\"" << endl;
			if (curChar() == '\'' && nextChar() == '\'') pushChar();
			if ((curChar() == '\'' && nextChar() != '\'') || isEOF()) stringEnd = true;
		} while (!stringEnd);

		if (curChar() == '\'') return handleFoundTokenOfType(STRING);
		else if (isEOF()) return handleFoundTokenOfType(UNDEFINED, (curChar() == '\n'));
	}
}

Token Tokenizer::try_COMMENT()
{
	if (curChar() == '#') {
		bool commentEnd = false;

		// MultiLine Comment
		if (nextChar() == '|') {
			pushChar(); // Push #

			do {
				if (curChar() == '\n') lineCtr++;
				pushChar();
				if ((curChar() == '|' && nextChar() == '#') || isEOF()) commentEnd = true;
			} while (!commentEnd);

			if (curChar() == '|') {
				pushChar(); // Push |
				return handleFoundTokenOfType(COMMENT); // Will push #
			}
			else if (isEOF()) return handleFoundTokenOfType(UNDEFINED, (curChar() == '\n'));
		}

		// Inline Comment
		else {
			do {
				pushChar();
				if (nextChar() == '\n' || isEOF()) commentEnd = true;
			} while (!commentEnd);

			if (nextChar() == '\n') {
				pushChar(); // Push last char of comment before \n
				return handleFoundTokenOfType(COMMENT, false);
			}
			else if (isEOF()) return handleFoundTokenOfType(UNDEFINED, (curChar() == '\n'));
		}
	}

}




// KEYWORDS

Token Tokenizer::try_SCHEMES()
{
	if (curChar() == 'S') {
		pushChar();

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
}

Token Tokenizer::try_FACTS()
{
	if (curChar() == 'F') {
		pushChar();

		if (curChar() == 'a') pushChar();
		else return try_ID();

		if (curChar() == 'c') pushChar();
		else return try_ID();

		if (curChar() == 't') pushChar();
		else return try_ID();

		if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return handleFoundTokenOfType(FACTS);
		else return try_ID();
	}
}

Token Tokenizer::try_QUERIES()
{
	if (curChar() == 'Q') {
		pushChar();

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
}

Token Tokenizer::try_RULES()
{
	if (curChar() == 'R') {
		pushChar();

		if (curChar() == 'u') pushChar();
		else return try_ID();

		if (curChar() == 'l') pushChar();
		else return try_ID();

		if (curChar() == 'e') pushChar();
		else return try_ID();

		if (curChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return handleFoundTokenOfType(RULES);
		else return try_ID();
	}
}

Token Tokenizer::try_ID()
{
	if (isEOF() || isspace(curChar())) return handleFoundTokenOfType(ID, false);
	
	switch (curChar())
	{
		// Special Characters
		case ',': return handleFoundTokenOfType(ID,false);
		case '.': return handleFoundTokenOfType(ID,false);
		case '?': return handleFoundTokenOfType(ID,false);
		case '(': return handleFoundTokenOfType(ID,false);
		case ')': return handleFoundTokenOfType(ID,false);
		case ':': return handleFoundTokenOfType(ID,false);
		case '*': return handleFoundTokenOfType(ID,false);
		case '+': return handleFoundTokenOfType(ID,false);
		case '\'': return handleFoundTokenOfType(ID, false);
		case '#': return handleFoundTokenOfType(ID, false);
		default:
			pushChar();
			return try_ID();
	}
}
