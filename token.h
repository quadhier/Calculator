#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using std::string;

class Tag
{
public:
	static const int INTNUM = 256;
	static const int DOUBLENUM = 257;
	static const int ID = 258;
	static const int RESERVED = 259;
};

class Token
{
public:
	int tag;
	Token(int t) { tag = t; }
	virtual ~Token() {  }
	static Token * add(Token *op1, Token *op2);
	static Token * minus(Token *op1, Token *op2);
	static Token * mul(Token *op1, Token *op2);
	static Token * div(Token *op1, Token *op2);
};

class IntNum : public Token
{
private:
public:
	int value;
	IntNum(int v): Token(Tag::INTNUM), value(v) {  }
};

class DoubleNum : public Token
{
private:
public:
	double value;
	DoubleNum(double v): Token(Tag::DOUBLENUM), value(v) {  }
};

class Word : public Token
{
private:
public:
	string lexeme;
	int intn;
	double doubn;
	char isi; // 0 for uninitialized, 1 for int, 2 for double
	Word(): Token(0), lexeme(""), intn(0), doubn(0), isi(0) {  }
	Word(int t, string s): Token(t), lexeme(s), intn(0), doubn(0), isi(0) {  }
	Word(Word& w): Token(w.tag), lexeme(w.lexeme), intn(w.intn), doubn(w.doubn), isi(w.isi) {  }
};

#endif
