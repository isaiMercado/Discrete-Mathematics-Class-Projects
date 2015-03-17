/*
 * Parameter.h
 *
 *  Created on: Jul 1, 2014
 *      Author: misaie
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Parameter
{
	string noquote;
	string quote;
	bool hasnoquote;
	bool hasquote;

public:

	Parameter()
	{

		hasnoquote = false;
		hasquote = false;

	};
	~Parameter(){};

	string printS()

	{

		if (noquote.length() != 0)

		return noquote;

		if (quote.length() != 0)

		return quote;

	}

	bool getBooloQuote()
	{

		return hasnoquote;

	}

	bool getBoolQuote()
	{

		return hasquote;

	}

	void setnoQuote(string x)
	{

		noquote = x;

		hasnoquote = true;
		hasquote = false;

	}

	void setQuote(string x)
	{

		quote = x;

		hasnoquote = false;
		hasquote = true;

	}

	void setbool()

	{

		if (quote.length() == 0)

			hasquote = false;

		else if (quote.length() != 0)

			hasquote = true;

		if (noquote.length() == 0)

			hasnoquote = false;

		else if (noquote.length() != 0)

			hasnoquote = true;

	}

	void clear()

	{

		noquote.clear();
		quote.clear();
		hasnoquote = false;
		hasquote = false;

	}


};



#endif /* PARAMETER_H_ */
