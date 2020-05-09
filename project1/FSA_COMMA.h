#pragma once
#include "Automaton.h"
class FSA_COMMA :
	public virtual Automaton
{
public:
	FSA_COMMA() {
		type = COMMA;
	};

	int Read(string& input) {
		if (curCharOf(input) == ',') {
			advanceChar();
		}
		return readIdx;
	}
};