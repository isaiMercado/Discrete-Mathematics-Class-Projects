/*
 * Scanner.h
//change
 *
 *  Created on: Jun 25, 2014
 *      Author: misaie
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<locale>
#include"Token.h"

#include"Parser.h"


using namespace std;





class Scanner
{
protected:

	vector<Token> listTokens;

	string text;

	token type;

	string value;

	int line;

	stack<char> paren;

	string error;

	stack<char> quote;

public:

	Scanner()

	{

		line = 1;

	}

	~Scanner(){}

	vector<Token> getVectorToken()
	{

		return listTokens;

	}


	void scan(string entry)
	{

		text = entry;

		scan_start();

		Parser machine;

		machine.parse(listTokens);

	}

	void scan_start()
	{

		comment_remover();


		for(unsigned int i = 0 ; i < text.length() ; i++)

		{
			//cout << "from for " << text[i] << endl;

			if (isalpha(text[i])) i = scan_ALPHA(i);

			else if (text[i] == EOF || text[i] == '\0') break;

			else i = scan_NOALPHA(i);

		}

	}




	void comment_remover()

		{

			//cout << "In comment remover " << endl;

			string no_comments = "";

			for (unsigned int i = 0 ; i < text.length() ; i++)

			{

				//cout << "inside for " << everything[i] << endl;
				if (text[i] != '#')

					no_comments = no_comments + text[i];

				else if (text[i] == '#')

				{

					while (text[i] != '\n')

					{

						//cout << "inside while " << everything[i] << endl;

						i++;

					}

					no_comments = no_comments + "\n";

				}

			}

			//cout << "no_comments \n" << no_comments << endl;

			text = no_comments;

		}



	int scan_ALPHA(int x)

		{

			//cout << "inside alpha " << text[x] << endl;

			string compare;

			while(isalpha(text[x]) || isdigit(text[x]))

			{

				//cout << "inside while " << text[x] << endl;

				 if (x < text.length())

				 {
					compare = compare + text[x];

					x++;

				 }

			}

			x--;


			if (compare == "Schemes" ) x = scan_SCHEMES(x, compare);

			else if (compare == "Facts" ) x = scan_FACTS(x, compare);

			else if (compare == "Rules" ) x = scan_RULES(x, compare);

			else if (compare == "Queries" ) x = scan_QUERIES(x, compare);

			else x = scan_ID(x, compare);

			return x;

		}



	int scan_NOALPHA(int x)

	{

		//cout << "inside no alpha " << text[x] << endl;

		char temp = text[x];

		switch (temp)

		{

			case '\n' : x = scan_LINE(x); break;

			case ' '  : break;

			case '\t' : break;

			case '\r' : break;

			case '\v' : break;

			case '\f' : break;

			case '\0' : break;

			case EOF : break;

			case ',' : x = scan_COMMA(x); break;

			case '.' : x = scan_PERIOD(x); break;

			case '?' : x = scan_Q_MARK(x); break;

			case '(' : x = scan_LEFT_PAREN(x); break;

			case ')' : x = scan_RIGHT_PAREN(x); break;

			case ':' : switch (text[x+1])

						{

							case '-' : x = scan_COLON_DASH(x); break;

							default : x = scan_COLON(x); break;

						} break;

			case '\'' : x = scan_QUOTE(x); break;

			default :

			{

				//cout << "no alpha error " << text[x] << endl;

				stringstream ss;

				ss << "Input Error on line " << line << "\n";

				error = ss.str();

				return text.length();

			} break;

		}

		return x;

	}







	int scan_LINE(int x)

	{

		//cout << "inside LINE " << endl;

		line++;

		return x;

	}


	int scan_COMMA(int x)

	{

		//cout << "inside COMMA " << endl;

		type = COMMA;

		value = ",";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_PERIOD(int x)

	{

		//cout << "inside PERIOD " << endl;

		type = PERIOD;

		value = ".";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_Q_MARK(int x)

	{

		//cout << "inside Q MARK " << endl;

		type = Q_MARK;

		value = "?";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_LEFT_PAREN(int x)

	{

		//cout << "inside LEFT PAREN " << endl;

		/*cout << "in left" << endl;

		switch (paren.size())
		{

		case 0 : paren.push('('); break;

		default :

				{

					//cout << "Input Error on line " << line << endl;

					stringstream ss;

					ss << "Input Error on line " << line << "\n";

					error = ss.str();

				} break;


		}


		switch(error.length())
		{

		case 0 : break;

		default : return text.length();

		}

		if (paren.size() != 0)

				cout << "left paren " << paren.top() << endl;

				cout << "left paren size " << paren.size() << endl;

		//cout << "after switch " << endl;*/



		type = LEFT_PAREN;

		value = "(";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_RIGHT_PAREN(int x)

	{

		//cout << "inside RIGHT PAREN " << endl;

		/*cout << "in right" << endl;

		switch (paren.size())

		{

		case 0 :
		{

			//cout << "Input Error on line " << line << endl;

			stringstream ss;

			ss << "Input Error on line " << line << "\n";

			error = ss.str();

		} break;

		default :

		{

			switch (paren.top())

			{

			case '(' : paren.pop(); cout << "inside pop " << endl; break;

			default :
				{

					//cout << "Input Error on line " << line << endl;

					stringstream ss;

					ss << "Input Error on line " << line << "\n";

					error = ss.str();

				} break;

			}

		}

		}

		switch(error.length())
		{

		case 0 : break;

		default : return text.length();

		}

		if (paren.size() != 0)

				cout << "right paren " << paren.top() << endl;

				cout << "right paren size " << paren.size() << endl;*/

		type = RIGHT_PAREN;

		value = ")";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_COLON(int x)

	{

		//cout << "inside COLON " << endl;

		type = COLON;

		value = ":";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_COLON_DASH(int x)

	{

		//cout << "inside COLON DASH " << endl;

		type = COLON_DASH;

		value = ":-";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x + 1;

	}






	int scan_SCHEMES(int x , string compare)

	{

		type = SCHEMES;

		value = compare;

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_FACTS(int x , string compare)

	{

		type = FACTS;

		value = compare;

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_RULES(int x , string compare)

	{

		type = RULES;

		value = compare;

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_QUERIES(int x , string compare)

	{

		type = QUERIES;

		value = compare;

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_ID(int x , string compare)

	{

		//cout << "inside ID " << endl;

		type = ID;

		value = compare;

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}



	int scan_QUOTE(int x)

	{

		//cout << "text x" << text[x] << endl;

		int b = x;

		while (text[b] != '\n' && b < text.length())

		{

			//cout << "text b" << text[b] << endl;

			switch (text[b])
			{

				case '\'' :
				{

					switch (quote.size())

					{

					case 0 : quote.push('\''); break;

					default : quote.pop(); break;

					} break;

				}

			}

		b++;

		}


		switch(quote.size())
		{

			case 0 : break;

			default :

			{

			stringstream ss;

			ss << "Input Error on line " << line << "\n";

			error = ss.str();

			return text.length();

			} break;

		}


		string comment;

		x++;

		while (text[x] != '\'')

		{

		//cout << "text " << text[x] << " " << x << endl;

		comment = comment + text[x];

		x++;

		}

		type = STRING;

		value = "'" + comment + "'";

		Token newtoken (type,value,line);

		listTokens.push_back(newtoken);

		return x;

	}


	void showvector()
	{

		for (unsigned int i = 0 ; i < listTokens.size() ; i++)

		{

			cout << "(" << listTokens[i].getStoken() << ",\"" << listTokens[i].getvalue() << "\"," << listTokens[i].getline() << ")" << endl;

		}

		switch (error.length())

		{

			case 0 : cout << "Total Tokens = " << listTokens.size() << endl; break;

			default : cout << error; break;


		}

	}

	string make_string()

	{

		stringstream ss;

		for (unsigned int i = 0 ; i < listTokens.size() ; i++)

		{

			ss << "(" << listTokens[i].getStoken() << ",\"" << listTokens[i].getvalue() << "\"," << listTokens[i].getline() << ")" << endl;

		}

		switch (error.length())
		{

			case 0 :

					{

					ss << "Total Tokens = " << listTokens.size();

					return ss.str();

					} break;

			default :

					{

					ss << error;

					return ss.str();

					} break;


		}



	}



};
#endif /* SCANNER_H_ */
