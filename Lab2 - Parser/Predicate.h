/*
 * Predicate.h
 *
 *  Created on: Jul 1, 2014
 *      Author: misaie
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include<iostream>
#include<string>
#include<vector>
#include"Parameter.h"

using namespace std;

class Predicate

{




string name;

vector<Parameter> params;

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

Predicate(){}

~Predicate(){}

string getName()
{

	return name;

}

vector<Parameter> getVectorParams()
{

	return params;

}

void setname(string x)
{

	name = x;

}

void pushVectorParams(Parameter x)
{

	params.push_back(x);

}

void setVectorParams(vector<Parameter> x)
{

	params = x;

}

void clearvector()

{

	params.clear();

}

string printS()

{

	string all;

	all = name + "(";

	for (unsigned int i = 0 ; i < params.size() ; i++)

	{

		all = all + params[i].printS();

		if (i+1 < params.size())

		{

			all = all + ",";

		}

	}

	all = all + ")";

	return all;

}

void clear()

{

	params.clear();

	name.clear();

}

};



#endif /* PREDICATE_H_ */
