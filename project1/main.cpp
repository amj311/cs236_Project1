#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Lexer.h"
#include "TEST.h"

int main(int argc, char** argv)
{

    ifstream ifs(argv[1]);
    string content((istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>()));

    Lexer lexer(content);
    lexer.tokenizeInput();
    //TEST test(content);

    cout << "Here." << endl;

    cout << "now here." << endl;
    
    return 0;
}