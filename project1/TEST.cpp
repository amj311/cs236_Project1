#include "TEST.h"

TEST::TEST(string& input)
{
	this->input = input;
	cout << "Made a new TEST with input: " << this->input << endl;
}