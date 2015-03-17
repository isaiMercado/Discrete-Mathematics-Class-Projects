/*
 * DataLog.h
 *
 *  Created on: Jul 1, 2014
 *      Author: misaie
 */

#ifndef DATALOG_H_
#define DATALOG_H_

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<sstream>
#include<iterator>
#include"Predicate.h"
#include"Rule.h"

using namespace std;

class DataLog
{
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Rule> Rules;
	vector<Predicate> Queries;
	set<string> Domain;

public:

	DataLog()
	{}

	~DataLog()
	{}

	void popRule()

	{

		Rules.pop_back();

	}

	void popQuery()

	{

		Queries.pop_back();

	}

	vector<Predicate> getVectorSchemes()
	{

		return Schemes;

	}

	vector<Predicate> getVectorFacts()
	{

		return Facts;

	}

	vector<Rule> getVectorRules()
	{

		return Rules;

	}

	vector<Predicate> getVectorQueries()
	{

		return Queries;

	}

	set<string> getSetDomain()
	{

		return Domain;

	}




	void pushVectorSchemes(Predicate x)
	{

		Schemes.push_back(x);

	}

	void pushVectorFacts(Predicate x)
	{

		Facts.push_back(x);

	}

	void pushVectorRules(Rule x)
	{

		Rules.push_back(x);

	}

	void pushVectorQueries(Predicate x)
	{

		Queries.push_back(x);

	}

	void pushSetDomain(string x)
	{

		Domain.insert(x);

	}



	void setVectorSchemes(vector<Predicate> x)
	{

		Schemes = x;

	}

	void setVectorFacts(vector<Predicate> x)
	{

		Facts = x;

	}

	void setVectorRules(vector<Rule> x)
	{

		Rules = x;

	}

	void setVectorQueries(vector<Predicate> x)
	{

		Queries = x;

	}

	void setDomain(set<string> x)
	{

		Domain = x;

	}

	string printS()

	{

		string all;

		all = printSschemes();

		all = all + printSfacts();

		all = all + printSrules();

		all = all +  printSqueries();

		all = all + printSdomain();

		return all;

	}

	string printSschemes()

	{

		stringstream all;

		all << "Schemes(" << Schemes.size() << "):\n";

		for (unsigned int i = 0 ; i < Schemes.size() ; i++)

		{

			all << "  " << Schemes[i].printS() << "\n";

		}


		return all.str();

	}

	string printSfacts()

	{

		stringstream all;

		all << "Facts(" << Facts.size() <<"):\n";

		for (unsigned int i = 0 ; i < Facts.size() ; i++)

		{

			all << "  " << Facts[i].printS() << "\n";

		}


		return all.str();

	}

	string printSrules()

	{

		stringstream all;

		all << "Rules(" << Rules.size() <<"):\n";

		for (unsigned int i = 0 ; i < Rules.size() ; i++)

		{

			all << "  " << Rules[i].printS() << "\n";////////////////////////////


		}


		return all.str();

	}


	string printSqueries()

	{

		stringstream all;

		all << "Queries(" << Queries.size() <<"):\n";

		for (unsigned int i = 0 ; i < Queries.size() ; i++)

		{

			all << "  " << Queries[i].printS() << "\n";

		}


		return all.str();

	}


	string printSdomain()

	{

		stringstream all;

		set<string>::iterator it;

		all << "Domain(" << Domain.size() <<"):\n";

		for (it = Domain.begin() ; it != Domain.end() ; it++)

		{

			all << "  "  << it->data() << "\n";

		}


		return all.str();

	}


};




#endif /* DATALOG_H_ */
