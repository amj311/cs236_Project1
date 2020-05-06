#include <iostream>
using namespace std;

#include "Lexer.h"

int main() {
	string myString = "this is a string";

	Lexer lexer = Lexer(myString);
	return 0;
}