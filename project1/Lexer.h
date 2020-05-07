#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
using namespace std;

#include "Token.h"

class Lexer
{
private:
public:
	Lexer(string& input);

	string input;
};

#endif
