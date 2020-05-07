#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include "TokenTypes.h"
using namespace std;

class Token
{
private:
	TOKEN_TYPE type;
	string value;
	int line;
public:
	Token(TOKEN_TYPE type, string value, int line);

	// GETTERS
	TOKEN_TYPE getType();
	string getValue();
	int getLine();

	string toString();
};



#endif // !TOKEN_H