#ifndef TOKEN_H_
#define TOKEN_H_

#include<iostream>
#include<string>

using namespace std;

enum token {COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,COLON_DASH,SCHEMES,FACTS,RULES,QUERIES,ID,STRING};

class Token

{

protected:

	token type;

	string Stoken;

	string value;

	int line;

public:

	Token(token type, string value, int line)

	{
		this->type = type;
		this->value = value;
		this->line = line;
	}

	~Token()
	{}

	void settoken(token x)

	{

		type = x;

	}



	void setvalue(string x)

	{

		value = x;

	}



	void setline(int x)

	{

		line = x;

	}


	string getStoken()
	{
		switch (type)

		{

		case COMMA       : Stoken = "COMMA"; break;

		case PERIOD      : Stoken = "PERIOD"; break;

		case Q_MARK      : Stoken = "Q_MARK"; break;

		case LEFT_PAREN  : Stoken = "LEFT_PAREN"; break;

		case RIGHT_PAREN : Stoken = "RIGHT_PAREN"; break;

		case COLON       : Stoken = "COLON"; break;

		case COLON_DASH  : Stoken = "COLON_DASH"; break;

		case SCHEMES     : Stoken = "SCHEMES"; break;

		case FACTS       : Stoken = "FACTS"; break;

		case RULES       : Stoken = "RULES"; break;

		case QUERIES     : Stoken = "QUERIES"; break;

		case ID          : Stoken = "ID"; break;

		case STRING      : Stoken = "STRING"; break;

		}

		return Stoken;

	}



	token gettoken()

	{

		return type;

	}



	string getvalue()

	{

		return value;

	}



	int getline()

	{

		return line;

	}



	void show()

	{

		cout << "(" << getStoken() << ",\"" << value << "\"," << line << ")\n";

	}

	string printS ()

	{

		stringstream ss;

		ss << "(" << getStoken() << ",\"" << value << "\"," << line << ")\n";

		return ss.str();

	}


};




#endif /* TOKEN_H_ */
