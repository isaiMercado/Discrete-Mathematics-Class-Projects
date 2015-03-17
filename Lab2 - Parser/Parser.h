/*
/; * Parser.h
 *
 *  Created on: Jul 1, 2014
 *      Author: misaie
 */

#ifndef PARSER_H_
#define PARSER_H_

#include<iostream>
#include<string>
#include<vector>

#include"Scanner.h"
#include"Token.h"

#include"Predicate.h"
#include"Parameter.h"
#include"Rule.h"
#include"DataLog.h"


using namespace std;

class Parser

{

	vector<Token> tokenlist;

	unsigned int index;

	string error;

	DataLog dat;







	Predicate pre;

	Parameter par;

	Rule rul;

	vector<Parameter> parVec;

	vector<Predicate> preVec;

	vector<Rule> ruleVec;




public:

	Parser(){index = 0;}

	~Parser(){}

	void parse(vector<Token> x)

	{

		////cout << "in parsing " << endl;

		tokenlist = x;

		datalogProgram();

	}

	void match(int x)

	{

		////cout << "before match " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if ( index < tokenlist.size())

		{

			index++;

		}

	}

	void datalogProgram()
	{

		//cout << "in datalogprogram " << endl;



		try

		{

			firstScheme();

			firstFact();

			firstRule();

			firstQuery();

			//cout << "index " << index << " size " << tokenlist.size() << endl;

		}

		catch (...)

		{

			error = "Failure!\n"; //cout<<"Error on line "<< tokenlist[index].getline()<< endl;

		}

	}

	void firstScheme()

	{

		//cout << "in first scheme token: " << tokenlist[index].getStoken() << endl;

		if (7 == tokenlist[index].gettoken()) // should be Schemes or error otherwise

		{

			match(tokenlist[index].gettoken());

			if (5 == tokenlist[index].gettoken()) // should be : or error otherwise

			{

				match(tokenlist[index].gettoken());

				schemeList();

				pre.clearvector();

				pre.setname("");

			}

			else

			{

				//cout << "Error from first scheme " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from first scheme " << endl;

			throw 0;

		}

	}

	void firstFact()

	{

		//cout << "in first fact " << endl;

		if (8 == tokenlist[index].gettoken())// should be Facts or error otherwise

		{

			match(tokenlist[index].gettoken());

			if (5 == tokenlist[index].gettoken()) // should be : or error otherwise

			{

				match(tokenlist[index].gettoken());

				factList();

				pre.clearvector();

				pre.setname("");

			}

			else

			{

				//cout << "Error from first fact " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from first fact " << endl;

			throw 0;

		}

	}

	void firstRule()

	{

		//cout << "in first rule " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (9 == tokenlist[index].gettoken()) // should be Rules or error otherwise

		{

			match(tokenlist[index].gettoken());

			if (5 == tokenlist[index].gettoken()) // should be : or error otherwise

			{

				//cout << "in first rule 2 " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

				match(tokenlist[index].gettoken());

				ruleList();

			}

			else

			{

				//cout << "Error from first rule " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from first rule " << endl;

			throw 0;

		}

	}

	void firstQuery()

	{

		//cout << "in first query " << endl;

		if (10 == tokenlist[index].gettoken()) // should be Queries or error otherwise

		{

			match(tokenlist[index].gettoken());

			if (5 == tokenlist[index].gettoken()) // should be : or error otherwise

			{

				match(tokenlist[index].gettoken());

				queryList();

			}

			else

			{

				//cout << "Error from first query " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from first query " << endl;

			throw 0;

		}

	}

	void schemeList()

	{

		//cout << "in scheme list " << endl;

		if ( 11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			scheme();

			dat.pushVectorSchemes(pre);

			if ( 11 == tokenlist[index].gettoken()) // should be ID optional

			{

				schemeList();

			}

		}

		else

		{

			//cout << "Error from schemelist " << endl;

			throw 0;

		}

	}

	void scheme()

	{

		//cout << "in scheme " << endl;

		predicate();

	}

	void factList()

	{

		//cout << "in factlist " << endl;

		if (11 == tokenlist[index].gettoken())// should be ID optional

		{

			fact();

			dat.pushVectorFacts(pre);

			pre.clear();

			if (11 == tokenlist[index].gettoken()) // should be ID optional

			{

				factList();

			}

		}

	}

	void fact()

	{

		//cout << "in fact " << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			predicate();

			if (1 == tokenlist[index].gettoken()) // should be period or error otherwise

			{

				match(tokenlist[index].gettoken());

			}

			else

			{

				//cout << "Error from fact " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from fact " << endl;

			throw 0;

		}

	}

	void ruleList()

	{

		//cout << "in rulelist " << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID optional

		{

			rule();

			dat.pushVectorRules(rul);///////////////////////////////////////

			rul.clear();

			if (11 == tokenlist[index].gettoken()) // should be ID optional

			{

				ruleList();


			}

		}

	}

	void rule()

	{

		//cout << "in rule " << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			predicate();

			rul.setHead(pre);////////////////////////////////////////

			pre.clear();

			if (6 == tokenlist[index].gettoken()) // should be colon-dash or error otherwise

			{

				match(tokenlist[index].gettoken());

				if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

				{

					predicateList();

					rul.setVector(preVec);

					preVec.clear();

					if (1 == tokenlist[index].gettoken()) // should be period or error otherwise

					{

						match(tokenlist[index].gettoken());

					}

					else

					{

						//cout << "Error from rule " << endl;

						throw 0;

					}

				}

				else

				{

					//cout << "Error from rule " << endl;

					throw 0;

				}

			}

			else

			{

				//cout << "Error from rule " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from rule " << endl;

			throw 0;

		}

	}

	void queryList()

	{

		//cout << "in querylist " << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			query();

			dat.pushVectorQueries(pre);

			pre.clear();

			if (index < tokenlist.size()) // protecting from going outside the vector

			{

				if (11 == tokenlist[index].gettoken()) // should be ID optional

				{

					//cout << "in querylist 2"  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

					queryList();

				}

			}

		}

		else

		{

			//cout << "Error from querylist " << endl;

			throw 0;

		}

	}

	void query()

	{

		//cout << "in query "  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			predicate();

			if (2 == tokenlist[index].gettoken()) // should be ? or error otherwise

			{

				//cout << "in query "  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

				match(tokenlist[index].gettoken());

				check_end();

			}

			else

			{

				//cout << "Error from query " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from query " << endl;

			throw 0;

		}



	}

	void check_end()

	{

		//cout << "index " << index << " size " << tokenlist.size() << endl;

		if (index < tokenlist.size())

		{

			if (tokenlist[index].gettoken() != 11)

			{

				throw 0;

			}

		}

	}

	void predicateList()

	{

		//cout << "in predicatelist "  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			predicate();

			preVec.push_back(pre);//////////////////////////////////

			pre.clear(); //////////////////////////////////////

			if (0 == tokenlist[index].gettoken()) // should be comma optional

			{

				//cout << "in predicatelist 2 "  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

				match(tokenlist[index].gettoken());

				//cout << "in predicatelist 3 "  << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

				predicateList();

			}

		}

		else

		{

			//cout << "Error from predicatelist " << endl;

			throw 0;

		}

	}

	void predicate() // creates a predicate object con ID y vector de parameter list

	{

		//cout << "out predicate 1 " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (11 == tokenlist[index].gettoken()) // should be ID or error otherwise

		{

			pre.setname(tokenlist[index].getvalue());

			match(tokenlist[index].gettoken());


			if (3 == tokenlist[index].gettoken()) // should be ( or error otherwise

			{

				match(tokenlist[index].gettoken());


				if (11 == tokenlist[index].gettoken() || 12 == tokenlist[index].gettoken()) // should be ID or error otherwise

				{

					parameterList();

					pre.setVectorParams(parVec);

					parVec.clear();


					if (4 == tokenlist[index].gettoken()) // should be ) or error otherwise

					{

						match(tokenlist[index].gettoken());

					}

					else

					{

						//cout << "Error from predicate " << endl;

						throw 0;

					}

				}

				else

				{

					//cout << "Error from predicate " << endl;

					throw 0;

				}

			}

			else

			{

				//cout << "Error from predicate " << endl;

				throw 0;

			}

		}

		else

		{

			//cout << "Error from predicate " << endl;

			throw 0;

		}

	}

	void parameterList() // creates vector of parameters

	{

		//cout << "in parameterlist " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (11 == tokenlist[index].gettoken() || 12 == tokenlist[index].gettoken()) // should be ID or String or error otherwise

		{

			parameter();

			parVec.push_back(par);

			par.clear();

			if (0 == tokenlist[index].gettoken()) // should be comma optional

			{

				//cout << "in parameterlist 2 " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

				match(tokenlist[index].gettoken());

				parameterList();

			}

		}

		else

		{

			//cout << "Error from parameter list " << endl;

			throw 0;

		}

	}

	void parameter() // creates parameter

	{

		//cout << "in parameter: " << tokenlist[index].getStoken() << " " << tokenlist[index].getvalue() << endl;

		if (11 == tokenlist[index].gettoken() || 12 == tokenlist[index].gettoken()) // should be ID or String or error otherwise

		{

			switch(tokenlist[index].gettoken())

			{

			case 11 : par.setnoQuote(tokenlist[index].getvalue()); break;

			case 12 :

				{

					par.setQuote(tokenlist[index].getvalue());

					dat.pushSetDomain(par.printS());

				} break;

			}

			match(tokenlist[index].gettoken());

		}

		else

		{

			////cout << "Error from parameter " << endl;

			throw 0;

		}

	}

	string printS()

	{

		string all;

		if (error.length() == 0)

		{

		all = "Success!\n" + dat.printS();


		}

		else

		{

		all = error + "  " + tokenlist[index].printS();

		}

		return all;

	}


	DataLog getDataLog ()

	{

		return dat;

	}


};



#endif /* PARSER_H_ */
