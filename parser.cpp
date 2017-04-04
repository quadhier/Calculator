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
	int tmpline = lr.line;
	if(pt1 && (pt1->tag == 256 || pt1->tag == 257 || pt1->tag == 258))
	{
	//	Token *pt2 = lr.scan();
	//	if(pt2)
	//	{
	//		if(pt2->tag != ')' || brc == 0)
	//			lr.back();
	//		else
	//			brc--;
	//		delete pt2;
	//	}
		if(pt1->tag == 258)
		{
			Word *pw = dynamic_cast<Word *>(pt1);
			if(pw->isi == 0)
			{
				delete pt1;
				cout<<"Error at line "<<tmpline<<": uninitialized variable '"<<pw->lexeme<<"'"<<endl;
				exit(1);
			}
			if(pw->isi == 1)
			{
				delete pt1;
				return new IntNum(pw->intn);
			}
			else // pw->isi == 2
			{	
				delete pt1;
				return new DoubleNum(pw->doubn);
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
		cout<<"Syntax error at line "<<lr.line<<": invalid expression"<<endl;
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
		Token *result = Token::mul(op1, op2);
		return hterm(result);
	}
	else // opt->tag == '/'
	{
		delete opt;
		Token *result = Token::div(op1, op2);
		return hterm(result);
	}
}

Token * Parser::term()
{
	Token *pt = factor();
	return hterm(pt);
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
		Token *result = Token::add(op1, op2);
		return hpart(result);
	}
	else // opt->tag == '-'
	{
		delete opt;
		Token *result = Token::minus(op1, op2);
		return hpart(result);
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
	int tmpline = lr.line;
	Token *pnt = lr.scan();
	if(pt->tag == 258)
	{
		/* 
		   For now, the expression can only have the form 'x = ...'
		*/
		if(!pnt || pnt->tag != '=')
		{
			cout<<"syntax error at line "<<tmpline<<": missing '=' "<<endl;
			if(pt)
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
			if(pi)
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

	int tmpline = 0;
	// If the first token of the statement is a identifier (not a keyword),
	// then it is an expression
	// Use exprn() to parse it 
	if(pt->tag == 258)
	{
		delete pt;
		lr.back();
		exprn();
		tmpline = lr.line;
		pt = lr.scan();
		if(!pt || pt->tag != ';')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing ';'"<<endl;
			if(pt)
				delete pt;
			exit(1);
		}
	}
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

		pbrc = lr.scan();
		if(!pbrc || pbrc->tag != ';')
		{
			cout<<"Syntax error at line "<<tmpline<<": missing ';'"<<endl;
			delete pt;
			if(pbrc)
				delete pbrc;
			exit(1);
		}		

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
	}

	delete pt;
	return true;
}
