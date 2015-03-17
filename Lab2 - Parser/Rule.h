/*
 * Rule.h
 *
 *  Created on: Jul 1, 2014
 *      Author: misaie
 */

#ifndef RULE_H_
#define RULE_H_

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include"Predicate.h"

using namespace std;

class Rule
{
	Predicate head;
	vector<Predicate> body;

	string ID;

public:

	void setID (string x)

	{

		ID = x;

	}

	string getID()

	{

		return ID;

	}

	Rule(){}
	~Rule(){}

	Predicate getHead()
	{

		return head;

	}

	vector<Predicate>  getBody()
	{

		return body;

	}

	void setHead(Predicate x)
	{

		head = x;

	}

	void pushVector(Predicate x)
	{

		body.push_back(x);

	}

	void setVector(vector<Predicate> x)
	{

		body =x;

	}

	void clear()

	{

		head.clear();

		body.clear();

	}


	string printS()

	{

		stringstream all;

		all << head.printS() << " :- ";

		for (int i = 0 ; i < body.size() ; i++)

		{

			all << body[i].printS();

			if (i+1 < body.size())

			{

				all << ",";

			}

		}

		return all.str();

	}
};



#endif /* RULE_H_ */
