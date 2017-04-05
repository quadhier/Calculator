#include <iostream>
#include "parser.h"
using std::cout;
using std::endl;

void Parser::parse()
{
	while(stmt());
}

Token * Parser::hfactor(Token *op1)
{
	return nullptr;
}

Token * Parser::factor()
{
	Token *pt1 = lr.scan();	
	tmpline = lr.line;
	if(pt1 && (pt1->tag == 256 || pt1->tag == 257 || pt1->tag == 258))
	{
		if(pt1->tag == 258)
		{
			Word *pw = dynamic_cast<Word *>(pt1);
			if(pw->isi == 0)
			{
				cout<<"Error at line "<<tmpline<<": uninitialized variable '"<<pw->lexeme<<"'"<<endl;
				delete pw;
				exit(1);
			}
			else if(pw->isi == 1)
			{
				int iv = pw->intn;
				delete pw;
				return new IntNum(iv);
			}
			else // pw->isi == 2
			{
				int dv = pw->doubn;
				delete pw;
				return new DoubleNum(dv);
			}	
		}
		else
			return pt1;
	}
	else if(pt1 && pt1->tag == '(')
	{
		Token *prt = part();
		Token *pt2 = lr.scan();
		if(pt2->tag != ')')
		{
			cout<<"Error at line "<<tmpline<<": missing right bracket"<<endl;
			exit(1);
		}
		delete pt1;
		delete pt2;
		return prt; 
	}
	else
	{
		cout<<"Syntax error at line "<<tmpline<<": invalid expression"<<endl;
		exit(1);
	}
}

Token * Parser::hterm(Token *op1)
{
	Token *opt = lr.scan();
	if(!opt || (opt->tag != '*' && opt->tag != '/'))
	{
		if(opt)
		{
			lr.back();
			delete opt;
		}
		return op1;
	}
	Token *op2 = factor();
	if(opt->tag == '*')
	{
		delete opt;
		Token *presult = Token::mul(op1, op2);
		return hterm(presult);
	}
	else // opt->tag == '/'
	{
		delete opt;
		Token *presult = Token::div(op1, op2);
		return hterm(presult);
	}
}

Token * Parser::term()
{
	Token *pf = factor();
	return hterm(pf);
}

Token * Parser::hpart(Token *op1)
{
	Token *opt = lr.scan();
	if(!opt || (opt->tag != '+' && opt->tag != '-'))
	{
		if(opt)
		{
			lr.back();
			delete opt;
		}
		return op1;
	}
	Token *op2 = term();
	if(opt->tag == '+')
	{
		delete opt;
		Token *presult = Token::add(op1, op2);
		return hpart(presult);
	}
	else // opt->tag == '-'
	{
		delete opt;
		Token *presult = Token::minus(op1, op2);
		return hpart(presult);
	}
}

Token * Parser::part()
{
	Token *pt = term();
	return hpart(pt);
}

void  Parser::exprn()
{
	Token *pt = lr.scan();
	tmpline = lr.line;
	Token *pnt = lr.scan();
	if(pt->tag == 258)
	{
		/* 
		   For now, the expression can only have the form 'x = ...'
		*/
		if(!pnt || pnt->tag != '=')
		{
			cout<<"syntax error at line "<<tmpline<<": missing '=' "<<endl;
			delete pt;
			if(pnt)
				delete pnt;
			exit(1);
		}
		// Use part() to parse the right of the expresion
		Token *presult = part();

		Word *pw = dynamic_cast<Word *>(pt);
		Word w = lr.words[pw->lexeme];
		if(presult->tag == 256)
		{	
			IntNum *pi = dynamic_cast<IntNum *>(presult);
			w.intn = pi->value;
			w.isi = 1;
			lr.words[w.lexeme] = w;
			delete pi;
		}
		else if(presult->tag == 257)
		{	
			DoubleNum *pd = dynamic_cast<DoubleNum *>(presult);
			w.doubn = pd->value;
			w.isi = 2;
			lr.words[w.lexeme] = w;
			if(pd)
			delete pd;
		}

	}
	
	if(pt)
		delete pt;
	if(pnt)
		delete pnt;
}

bool Parser::stmt()
{
	Token *pt = lr.scan();
	if(!pt)
		return false;

	// If the first token of the statement is a identifier (not a keyword),
	// then it is an expression
	// Use exprn() to parse it 
	if(pt->tag == 258)
	{
		delete pt;
		pt = nullptr;
		lr.back();
		exprn();
		tmpline = lr.line; // Store the line number of the expression
		pt = lr.scan();
		if(!pt || pt->tag != ';')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing ';'"<<endl;
			if(pt)
				delete pt;
			exit(1);
		}
	}
	// If it is a print statement
	// then print it
	else if(pt->tag == 259)
	{
		Word *pw = dynamic_cast<Word *>(pt);
		tmpline = lr.line;		
		Token *pbrc = lr.scan();
		if(!pbrc || pbrc->tag != '(')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing '('"<<endl;
			delete pt;
			if(pbrc)
				delete pbrc;
			exit(1);
		}
		delete pt;
		pt = part();
		tmpline = lr.line;
		delete pbrc;
		pbrc = lr.scan();
		if(!pbrc || pbrc->tag != ')')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing ')'"<<endl;
			delete pt;
			if(pbrc)
				delete pbrc;
			exit(1);
		}		
		delete pbrc;
		pbrc = lr.scan();
		if(!pbrc || pbrc->tag != ';')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing ';'"<<endl;
			delete pt;
			if(pbrc)
				delete pbrc;
			exit(1);
		}		
		// Print the value according to the type of the identifier
		if(pt->tag == 256)
		{
			IntNum *pi = dynamic_cast<IntNum *>(pt);
			cout<<pi->value<<endl;
		}
		if(pt->tag == 257)
		{
			DoubleNum *pd = dynamic_cast<DoubleNum *>(pt);
			cout<<pd->value<<endl;
		}				
		delete pbrc;
	}
	delete pt;
	return true;
}
