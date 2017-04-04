#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cctype>
#include "token.h"

class Lexer
{
private:
	int addsteps; // Record the characters extracted last time
	int addlines; // Record the lines added last time
	unsigned char nextc; // Current character
	std::ifstream ifs;
public:
	int line; // Current line
	std::map<std::string, Word> words; // Store the identifiers

	// Initialize the member variables and store the keywords
	Lexer(std::string filename);
	// Get the next token
	Token* scan();
 	// Undo scan()
	void back();
};

#endif
