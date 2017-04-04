#ifndef PARSER_H
#define PARSER_H

//#include "sytxnode.h"
#include "lexer.h"

class Parser
{
private:
	Lexer lr; // The lexer used to get the token
	int brc;
	Token * factor();
	Token * hfactor(Token *op1);
	Token * term();
	Token * hterm(Token *op1);
	Token * part();
	Token * hpart(Token *op1);
	void exprn();
	bool stmt();
public:
	// Initialize the lexer by giving it the input file
	Parser(std::string filename): lr(filename), brc(0) {  }
	// Parse the code	
	void parse();
};

#endif
