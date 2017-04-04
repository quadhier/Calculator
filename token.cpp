#include "token.h"

Token * Token::add(Token *op1, Token *op2)
{
	int t1 = op1->tag;
	int t2 = op2->tag;
	if(t1 == 256 && t2 == 256)
	{
		dynamic_cast<IntNum *>(op1)->value = dynamic_cast<IntNum *>(op1)->value + dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else if(t1 == 256 && t2 == 257)
	{
		dynamic_cast<DoubleNum *>(op2)->value = dynamic_cast<IntNum *>(op1)->value + dynamic_cast<DoubleNum *>(op2)->value;
		delete op1;
		return op2;
		
	}
	else if(t1 == 257 && t2 == 256)	
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value + dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value + dynamic_cast<DoubleNum *>(op2)->value;
		delete op2;
		return op1;
	}
}

Token * Token::minus(Token *op1, Token *op2)
{
	int t1 = op1->tag;
	int t2 = op2->tag;
	if(t1 == 256 && t2 == 256)
	{
		dynamic_cast<IntNum *>(op1)->value = dynamic_cast<IntNum *>(op1)->value - dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else if(t1 == 256 && t2 == 257)
	{
		dynamic_cast<DoubleNum *>(op2)->value = dynamic_cast<IntNum *>(op1)->value - dynamic_cast<DoubleNum *>(op2)->value;
		delete op1;
		return op2;
		
	}
	else if(t1 == 257 && t2 == 256)	
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value - dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value - dynamic_cast<DoubleNum *>(op2)->value;
		delete op2;
		return op1;
	}
}

Token * Token::mul(Token *op1, Token *op2)
{
	int t1 = op1->tag;
	int t2 = op2->tag;
	if(t1 == 256 && t2 == 256)
	{
		dynamic_cast<IntNum *>(op1)->value = dynamic_cast<IntNum *>(op1)->value * dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else if(t1 == 256 && t2 == 257)
	{
		dynamic_cast<DoubleNum *>(op2)->value = dynamic_cast<IntNum *>(op1)->value * dynamic_cast<DoubleNum *>(op2)->value;
		delete op1;
		return op2;
		
	}
	else if(t1 == 257 && t2 == 256)	
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value * dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value * dynamic_cast<DoubleNum *>(op2)->value;
		delete op2;
		return op1;
	}
}

Token * Token::div(Token *op1, Token *op2)
{
	int t1 = op1->tag;
	int t2 = op2->tag;
	if(t1 == 256 && t2 == 256)
	{
		dynamic_cast<IntNum *>(op1)->value = dynamic_cast<IntNum *>(op1)->value / dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else if(t1 == 256 && t2 == 257)
	{
		dynamic_cast<DoubleNum *>(op2)->value = dynamic_cast<IntNum *>(op1)->value / dynamic_cast<DoubleNum *>(op2)->value;
		delete op1;
		return op2;
		
	}
	else if(t1 == 257 && t2 == 256)	
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value / dynamic_cast<IntNum *>(op2)->value;
		delete op2;
		return op1;
	}
	else
	{
		dynamic_cast<DoubleNum *>(op1)->value = dynamic_cast<DoubleNum *>(op1)->value / dynamic_cast<DoubleNum *>(op2)->value;
		delete op2;
		return op1;
	}
}
