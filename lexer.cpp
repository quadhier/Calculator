#include "lexer.h"
using std::string;
using std::map;
using std::ifstream;
using std::isdigit;
using std::isspace;
using std::stoi;
using std::stod;
using std::isalpha;

using std::cout;
using std::endl;

Lexer::Lexer(string filename): ifs(filename), nextc(' '), line(1), addsteps(0), addlines(0)
{
	Word w(Tag::RESERVED, "print");
	words["print"] = w;
}

Token * Lexer::scan()
{
	addsteps = 0;
	addlines = 0;
  	while(true)
  	{
  		nextc = ifs.get();
		addsteps++;
		if(ifs.eof())
			return nullptr;
  		if(nextc == ' ' || nextc == '\t')
  			continue;
  		else if(nextc == '\n')
		{
  			line += 1;
			addlines++;
		}
  		else 
  			break;
  	}
  
  	if(isdigit(nextc))
  	{
  		string nums;
  		while(isdigit(nextc))
  		{
  			nums.push_back(nextc);
  			nextc = ifs.get();
			addsteps++;
  		}
		// The first nondigit char appears
  		if(isspace(nextc))
  		{
  			int intv = stoi(nums);
  			return new IntNum(intv);
  		}
  		else if(nextc == '.')
  		{
  			nums.push_back(nextc);
  			nextc = ifs.get();
			addsteps++;
  			while(isdigit(nextc))
  			{
  				nums.push_back(nextc);
  				nextc = ifs.get();
				addsteps++;
  			}
			//If the nextc is not a space, undo get()
			if(nextc != ' ')
			{
				ifs.unget();
				addsteps--;
			}
  			double doubv = stod(nums);
  			return new DoubleNum(doubv);
  		}
		else
		{
			//If the nextc is not a space, undo get()
			if(nextc != ' ')
			{
				ifs.unget();
				addsteps--;
			}
  			int intv = stoi(nums);
  			return new IntNum(intv);
		}
  	}
  	
  	if(isalpha(nextc) || nextc == '_')
  	{
  		string idt;
  		while(isdigit(nextc) || isalpha(nextc) || nextc == '_')
  		{
  			idt.push_back(nextc);
  			nextc = ifs.get();
			addsteps++;
  		}
		//If the nextc is not a space, undo get()
		if(nextc != ' ')
		{
			ifs.unget();
			addsteps--;
		}
		// Try to get the identifier from the symbol table
		// If it does not exit, make a new one and store it
  		if(words.count(idt))
  			return new Word(words.at(idt));
  		else
  		{
  			Word* w = new Word(Tag::ID, idt);
  			words[idt] = *w;
  			return w;
  		}
  	}
  		
  	return new Token(nextc);
}

void Lexer::back()
{
	while(addsteps--)
	{
		ifs.unget();
	}
	while(addlines--)
	{
		line--;
	}
	nextc = ' ';
}
