/*
 * interpreter.h
 *
 *  Created on: Jul 21, 2014
 *      Author: misaie
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include "Parser.h"
#include <sstream>

using namespace std;


class Pset : public set < int >

{};


class Scheme : public vector < string >

{

public:

	void coutScheme() const

	{

		for (unsigned int i = 0; i < size(); i++)

		{

			cout << at(i) << " ";

		}

		cout << endl;

	}


	string stringScheme() const

	{

		stringstream ss;

		for (unsigned int i = 0; i < size(); i++)

		{

			ss << at(i) << " ";

		}

		ss << endl;

		return ss.str();

	}

	void pushSchema(Scheme x)

	{

		//cout << "inside Tuple pushing Tuple" << endl;

		for (int a = 0; a < x.size(); a++)

		{

			//cout << "pushing " << x[a] << endl;

			push_back(x[a]);

			//cout << [a] << "was pushed back" << endl;

		}

	}


};







class Tuple : public vector < string >

{

public:

	void pushTuple(Tuple x)

	{

		//cout << "inside Tuple pushing Tuple" << endl;

		for (int a = 0; a < x.size(); a++)

		{

			//cout << "pushing " << x[a] << endl;

			push_back(x[a]);

			//cout << [a] << "was pushed back" << endl;

		}

	}

	void coutTuple() const

	{

		for (unsigned int i = 0; i < size(); i++)

		{

			cout << at(i) << " ";

		}

		cout << endl;

	}

	string stringTuple() const

	{

		stringstream ss;

		for (unsigned int i = 0; i < size(); i++)

		{

			ss << at(i) << " ";

		}

		ss << endl;

		return ss.str();

	}


};







class Relation

{

public:

	string name;

	Scheme attributes;

	Scheme variables;

	Scheme RulesVar;

	set<Tuple> tuples;

	int found;

	bool moreTuple;

	int TuplesBeforeRules;

	int TuplesAfterRules;



	Relation()

	{

		this->found = 0;

		this->moreTuple = false;

		this->TuplesBeforeRules = 0;

		this->TuplesAfterRules = 0;

	}

	~Relation()

	{

	}

	Relation select(vector<Parameter>  para)

	{

		Relation temp;

		set<Tuple> tup = tuples;

		select1(tup, para);

		temp.setName(name);

		temp.setAttributes(attributes);

		temp.setTupples(tup);

		temp.setFound(tup.size());

		temp.setVariables(variables);

		return temp;

	}


	Relation projectRules(vector<Parameter>  para)

	{

		Relation rel;

		vector<int> intvec;

		set<Tuple> tup;

		takeoutDuplicatesRules(para);

		intvec = takeoutStringsRules(para);

		intvec = checkingOrderRules(intvec);

		tup = projectingColumnsRules(intvec);



		rel.setName(name);

		rel.setAttributes(attributes);

		rel.setTupples(tup);


		//attributes.coutScheme();

		//rel.coutsetTuple(tup);


		rel.setFound(found);

		rel.setVariables(variables);

		return rel;

	}


	void takeoutDuplicatesRules(vector<Parameter> & para)

	{

		//cout << "In takeout Duplicates " << endl;

		bool c = false;

		//vector<Parameter> temp;

		Parameter Ptemp;

		for (unsigned int i = 0; i < para.size(); i++)

		{

			for (unsigned int a = 1 + i; a < para.size(); a++)

			{

				if (c == true) a = 1 + i;

				c = false;

				if (para[i].printS() == para[a].printS())

				{



					//temp.push_back(para[a]);

					para.erase(para.begin() + a);

					c = true;

				}

			}

		}

		//para = temp;

		//coutvectorPara(para);

		//return para;
	}




	vector<int> takeoutStringsRules(vector<Parameter> & para)

	{

		//cout << "In takeout String " << endl;

		vector<int> x;

	label:

		for (unsigned int i = 0; i < para.size(); i++)

		{

			//cout << "i " << i << " this is para " << para.at(i).printS() << " this is bool " << para.at(i).getBoolQuote() << endl;

			if (para.at(i).getBoolQuote() == true)

			{

				//cout << para.at(i).printS() << " erased " << endl;

				para.erase(para.begin() + i);

				x.push_back(i);

				goto label;

			}

		}

		for (int i = 0; i < para.size(); i++)

		{

			variables.push_back(para[i].printS());

		}

		//cout << "cout vector schemes " << endl<<endl;

		//coutvectorPara(para);

		//cout << endl;

		return x;

	}


	vector<int> checkingOrderRules(vector<int> & invec)

	{

		string temp;

		Scheme attri;

		Tuple tup;

		vector<Tuple> vecTup;

		set<Tuple>::iterator it;

		vecTup = convertsetTovector(tuples);

		for (int a = 0; a < variables.size(); a++)

		{

			for (int b = 0; b < attributes.size(); b++)

			{

				if (variables[a] == attributes[b])

				{

					temp = attributes[a];

					attributes[a] = attributes[b];

					attributes[b] = temp;

					temp.clear();

					for (int c = 0; c < vecTup.size(); c++)

					{

						for (int d = 0; d < vecTup[c].size(); d++)

						{

							if (d == b)

							{

								//cout << "swaping a = " << vecTup[c][a] << " and b = " << vecTup[c][b] << endl;

								temp = vecTup[c][a];

								//cout << "temp should be a " << temp << endl;

								vecTup[c][a] = vecTup[c][b];

								//cout << "it[a] should be b " << vecTup[c][a] << endl;

								vecTup[c][b] = temp;

								//cout << "itba] should be a " << vecTup[c][b] << endl;

								temp.clear();

							}

						}

					}

				}

			}

		}

		tuples = convertvectorToset(vecTup);//////////////////////////changing stufff


		return invec;

	}



	set<Tuple> projectingColumnsRules(vector<int> & intvec)

	{

		set<Tuple> tup = tuples;

		vector<Tuple> vec = convertsetTovector(tup);


		for (unsigned int i = 0; i < intvec.size(); i++)

		{

			for (unsigned int a = 0; a < vec.size(); a++)

			{

				for (unsigned int b = 0; b < vec[a].size(); b++)
				{

					//cout << "intvec[i] is " << intvec[i] << " b  is " << b << endl;

					if (intvec[i] == b)

					{

						//cout << "erasing " << vec[a][b] << endl;

						vec[a].erase(vec[a].begin() + b);



					}

				}


			}

		}



		//vec = erasingAfterVariables(vec);

		erasingAfterVariables(vec);

		tup = convertvectorToset(vec);

		setAttributes(variables);

		return tup;

	}

	Relation rename(vector<Parameter> para)

	{

		Relation rel;

		rename1(para);

		rel.setName(name);

		rel.setAttributes(attributes);

		rel.setTupples(tuples);

		rel.setFound(found);

		rel.setVariables(variables);

		return rel;


	}



	void setRulesVar(Scheme x)

	{

		RulesVar = x;

	}

	Scheme getRulesVar()

	{

		return RulesVar;

	}

	void pushVecAttributes(Scheme x)

	{

		for (int a = 0; a < x.size(); a++)

		{

			attributes.push_back(x[a]);

		}

	}

	void clear()

	{

		name.clear();

		attributes.clear();

		variables.clear();

		tuples.clear();

		found = 0;

		moreTuple = false;

		TuplesBeforeRules = 0;

		TuplesAfterRules = 0;

		RulesVar.clear();


	}

	bool getmoreTuple()

	{

		return moreTuple;

	}

	void setmoreTuple(bool x)

	{

		moreTuple = x;

	}

	void evaluatemoreTuple()

	{

		if (TuplesBeforeRules == TuplesAfterRules)

		{

			moreTuple = false;

		}

		else

		{

			moreTuple = true;

		}

	}

	void setTuplesBeforeRules()

	{

		TuplesBeforeRules = 0;

		TuplesBeforeRules = tuples.size();

	}

	void setTuplesAfterRules()

	{

		TuplesAfterRules = 0;

		TuplesAfterRules = tuples.size();

	}


	void rename1(vector<Parameter> & para)

	{

		Scheme sch;

		for (unsigned int g = 0; g < para.size(); g++)

		{

			sch.push_back(para[g].printS());

		}

		attributes = sch;

	}



	vector<Tuple> convertsetTovector(set<Tuple> & x)

	{

		vector<Tuple> vec;

		set<Tuple>::iterator it;

		for (it = x.begin(); it != x.end(); it++)

		{

			vec.push_back(*it);

		}

		return vec;

	}


	set<Tuple> convertvectorToset(vector<Tuple> & x)

	{

		set<Tuple> setT;

		set<Tuple>::iterator it;

		for (unsigned int i = 0; i < x.size(); i++)

		{

			setT.insert(x[i]);

		}

		return setT;

	}





	void erasingAfterVariables(vector<Tuple> & vec)

	{

		for (unsigned int a = 0; a < vec.size(); a++)

		{

			for (unsigned int b = 0; b < vec[a].size(); b++)
			{

				//cout << "intvec[i] is " << intvec[i] << " b  is " << b << endl;

				while (vec[a].size() > variables.size())

				{

					//cout << "checking tuples ";

					//vec[a].coutTuple();

					vec[a].pop_back();

				}

			}


		}

		//return vec;

	}





	void coutvectorPara(vector<Parameter> & para)

	{

		for (unsigned int i = 0; i < para.size(); i++)

		{

			cout << para[i].printS() << " ";

		}

		cout << endl;

	}



	void select1(set<Tuple> & tup, vector<Parameter> & para)

	{

		//cout << "\n\n++++++++++++++++++++++++++++++++SELECT in " << name << "\n" << endl;

		set<Tuple>::iterator it;

		//vector<Tuple> temp;

		//label:

		//temp = convertsetTovector(tup);

		for (unsigned int a = 0; a < para.size(); a++)

		{

		label:
			for (Tuple it : tup)
				//for (it = tup.begin(); it != tup.end() ; it++)
				//for (unsigned int b = 0 ; b < temp.size() ; b++)
			{

				//coutsetTuple(tup);

				//cout << para.at(a).printS() << " VS " << it->at(a) << endl;

				if ((para.at(a).printS() != it.at(a)) && para.at(a).getBoolQuote() == true)
					//if (para[a].printS() != temp[b][a]     &&     para[a].getBoolQuote() == true)
				{

					//cout << " ====Removed==== " << endl;

					tup.erase(it);

					//temp.erase(temp.begin() + b);

					goto label;

				}

			}

		}

		//tup = convertvectorToset(temp);

		//coutsetTuple(tup);

		//return tup;

	}


	void addTuples(set<Tuple> & x)

	{

		set<Tuple>::iterator it;

		int i = 1;

		for (it = x.begin(); it != x.end(); it++)

		{

			//cout << "this is being unified... " << i << " elements added "<< endl;

			tuples.insert(*it);

			i++;

		}

	}



	void pushTuples(Tuple x)

	{

		tuples.insert(x);

	}




	void coutsetTuple(set<Tuple> x)

	{

		set<Tuple>::iterator it;

		for (it = x.begin(); it != x.end(); it++)

		{

			it->coutTuple();

		}

	}



	void coutRelation()

	{

		set<Tuple>::iterator it;

		cout << endl << "Name is " << name << endl << endl;

		cout << "Attributes are ";

		for (unsigned int i = 0; i < attributes.size(); i++)

		{

			cout << attributes[i] << " ";

		}

		cout << endl << endl;

		cout << "Found is " << found << endl << endl;

		for (it = tuples.begin(); it != tuples.end(); it++)

		{

			//cout << "Parameters are ";

			for (unsigned int i = 0; i < it->size(); i++)

			{

				cout << (*it)[i] << " ";

			}

			cout << endl;

		}

		cout << "\nVariables are ";

		for (unsigned int i = 0; i < variables.size(); i++)

		{

			cout << variables[i] << " ";

		}

		cout << endl;

		cout << "\nRulesVar are ";

		for (unsigned int i = 0; i < RulesVar.size(); i++)

		{

			cout << RulesVar[i] << " ";

		}

		cout << endl << "------------------END-------------------" << endl << endl;

	}

	string getName()

	{

		return name;

	}

	set<Tuple> getTuples()

	{

		return tuples;

	}

	int getFound()

	{

		return found;

	}

	Scheme getAttributes()

	{

		return attributes;

	}

	Scheme getVariables()

	{

		return variables;

	}

	void pushAttributes(string x)

	{

		attributes.push_back(x);

	}

	void setName(string x)

	{

		name = x;

	}

	void setAttributes(Scheme x)

	{

		attributes = x;

	}

	void setTupples(set<Tuple> x)

	{

		tuples = x;

	}

	void setFound(int x)

	{

		found = x;

	}

	void setVariables(Scheme x)

	{

		variables = x;

	}

	int tuplesSize()

	{

		return tuples.size();

	}


	Relation project(vector<Parameter> para)

	{

		Relation rel;

		vector<int> intvec;

		set<Tuple> tup;

		takeoutDuplicates(para);

		intvec = takeoutStrings(para);

		tup = projectingColumns(intvec);

		rel.setName(name);

		rel.setAttributes(attributes);

		rel.setTupples(tup);

		rel.setFound(found);

		rel.setVariables(variables);

		return rel;

	}



	void takeoutDuplicates(vector<Parameter> & para)

	{

		//cout << "In takeout Duplicates " << endl;

		bool c = false;


		for (unsigned int i = 0; i < para.size(); i++)

		{

			for (unsigned int a = 1 + i; a < para.size(); a++)

			{

				if (c == true) a = 1 + i;

				c = false;

				if (para[i].printS() == para[a].printS())

				{

					para.erase(para.begin() + a);

					c = true;

				}

			}

		}

		//coutvectorPara(para);

		//return para;

	}



	vector<int> takeoutStrings(vector<Parameter> & para)

	{

		//cout << "In takeout String " << endl;

		vector<int> x;

	label:

		for (unsigned int i = 0; i < para.size(); i++)

		{

			////cout << "i " << i << " this is para " << para.at(i).printS() << " this is bool " << para.at(i).getBoolQuote() << endl;

			if (para.at(i).getBoolQuote() == true)

			{

				////cout << para.at(i).printS() << " erased " << endl;

				para.erase(para.begin() + i);

				x.push_back(i);

				goto label;

			}

		}

		for (int i = 0; i < para.size(); i++)

		{

			variables.push_back(para[i].printS());

		}

		//cout << "//cout vector schemes " << endl<<endl;

		//coutvectorPara(para);

		//cout << endl;

		return x;

	}


	set<Tuple> projectingColumns(vector<int> & intvec)

	{

		set<Tuple> tup = tuples;

		vector<Tuple> vec = convertsetTovector(tup);


		for (unsigned int i = 0; i < intvec.size(); i++)

		{

			for (unsigned int a = 0; a < vec.size(); a++)

			{

				for (unsigned int b = 0; b < vec[a].size(); b++)
				{

					//cout << "intvec[i] is " << intvec[i] << " b  is " << b << endl;

					if (intvec[i] == b)

					{

						//cout << "erasing " << vec[a][b] << endl;

						vec[a].erase(vec[a].begin() + b);



					}

				}


			}

		}

		tup = convertvectorToset(vec);

		return tup;

	}


};








class DataBase

{

private:

	map<string, Relation> Database;

	bool RelSizeChanged;

	int initialSize;

	int laterSize;

public:

	DataBase()

	{

		RelSizeChanged = false;

		initialSize = 0;

		laterSize = 0;

	}

	~DataBase(){}

	int getInitialSize()

	{

		initialSize = 0;

		for (auto i : Database)

		{

			initialSize = initialSize + i.second.tuplesSize();

		}

		return initialSize;

	}

	int getlaterSize()

	{

		laterSize = 0;

		for (auto i : Database)

		{

			laterSize = laterSize + i.second.tuplesSize();

		}

		return laterSize;

	}

	void setTuplesBeforeCounters()

	{


		for (auto i : Database)

		{

			i.second.setTuplesBeforeRules();

		}

	}

	void setTuplesAfterCounters()

	{

		for (auto &i : Database)

		{

			i.second.setTuplesAfterRules();

		}

	}


	void setAllReltoFalse()

	{

		for (auto &i : Database)

		{

			i.second.setmoreTuple(false);

		}

	}

	bool getRelSizeChanged()

	{

		for (auto &i : Database)

		{

			if (i.second.getmoreTuple() == true)

			{

				RelSizeChanged = true;

				return RelSizeChanged;

			}

		}

		return RelSizeChanged;

	}

	void setRelSizeChanged(bool x)

	{

		RelSizeChanged = x;

	}

	map<string, Relation>::iterator begin()

	{

		return Database.begin();

	}

	map<string, Relation>::iterator end()

	{

		return Database.end();

	}

	void coutRelation()

	{

		map<string, Relation>::iterator it;

		for (it = Database.begin(); it != Database.end(); it++)

		{

			it->second.coutRelation();

		}

	}



	int size()

	{

		return Database.size();

	}

	void Push(string key, Relation x)

	{

		Database[key] = x;

	}

	map<string, Relation> getDataBase()

	{

		return Database;

	}

};







class Interpreter

{

private:

	DataLog dat;

	DataBase Database;

	vector<Relation> outRel;

	int FPcounter;

	int test = 3;

public:

	DataBase getdatabase()

	{

		return Database;

	}

	Interpreter()

	{

		this->FPcounter = 1;

	}

	~Interpreter()

	{}

	DataLog getDataLog()

	{

		return dat;

	}

	void evaQuery(Predicate x)

	{

		dat.pushVectorQueries(x);

		//cout << "from interpreter query[0] " << dat.getVectorQueries()[0].printS() << endl;

		evaluateQuery();

		dat.popQuery();

		//outRel.clear();


	}

	void evaRule(Rule x)

	{

		dat.pushVectorRules(x);

		//cout << "begining round " << endl;

		readfacts2();

		//cout << "ending round " << endl;

		dat.popRule();


	}

	void setDatalog(DataLog x)

	{

		dat = x;

		readScheme();

		readFacts();

	}

	void readfacts2()

	{

		Relation temp;

		temp = Join(temp, 0);

		temp = Select(temp);

		temp = Project(temp);

		Union(temp);

		temp.clear();

	}

	void interprete(DataLog dat)

	{

		this->dat = dat;



		makeDataBase();

	}

	void makeDataBase()

	{

		readScheme();

		readFacts();

		readRules();

		evaluateQuery();

	}





	void readRules()

	{

		int initial = Database.getInitialSize();

		string stop;

		for (unsigned int i = 0; i < dat.getVectorRules().size(); i++)

		{



			//cout << "\n\nIN READ RULES >>> RECURSION " << FPcounter << endl<<endl;

			Relation temp;

			temp = Join(temp, i);

			//temp.coutRelation();

			//cout << "after join" << endl;

			//cin >> stop;

			temp = Select(temp);

			//temp.coutRelation();

			//cout << "after select" << endl;

			//cin >> stop;

			temp = Project(temp);

			//temp.coutRelation();

			//cout << "after project" << endl;

			//cin >> stop;

			Union(temp);

			//temp.coutRelation();

			//cout << "after UNION" << endl;

			//cin >> stop;

			temp.clear();


		}

		int later = Database.getlaterSize();

		if (initial != later)

		{

			FPcounter++;

			readRules();

		}

	}




	Relation Join(Relation & rel, unsigned int i)

	{

		//cout << "in join " << endl;




		set<Tuple> willEmpty;

		vector<Relation> vecRel;





		//cout << "in join 1" << endl;

		vecRel = prediToRel(i);

		set<Tuple> willReturn = vecRel[0].getTuples();

		Scheme schema = vecRel[0].getAttributes();

		//Scheme schema;

		//set<Tuple> willReturn;

		if (vecRel.size() == 1)

		{

			//cout << "in one relation" <<endl;

			rel = vecRel[0];

			rel.setName(dat.getVectorRules()[i].getHead().getName());

			rel.setRulesVar(setRulevar(i));

			return rel;

		}

		else

		{


			for (int a = 1; a < vecRel.size(); a++)

			{

				//for (int b = a + 1 ; b < vecRel.size() ; b++)

				//{

				//cout << "in join 2" << endl;

				schema = setSchema(a, vecRel, schema);

				Tuple temp;

				for (Tuple t1 : vecRel[a].getTuples())

				{



					//cout << "in join 3" << endl;


					for (Tuple t2 : willReturn)
					{

						//cout << "in join 4" << endl;

						if (canjoinQ(schema, t1, t2, temp) == true)

						{

							//willReturn.insert(temp);

							willEmpty.insert(temp);

							//cout << "cout tuple that is being inserted" << endl;

							//temp.coutTuple();

							temp.clear();

						}





					}


					//pushingsets(willReturn, willEmpty);



				}

				willReturn = willEmpty;

				willEmpty.clear();

			}



			rel.setName(dat.getVectorRules()[i].getHead().getName());

			rel.setAttributes(schema);

			rel.setTupples(willReturn);

			rel.setRulesVar(setRulevar(i));

		}

		return rel;

	}

	Scheme setRulevar(int i)

	{

		Scheme Stemp;

		for (int b = 0; b < dat.getVectorRules()[i].getHead().getVectorParams().size(); b++)

		{

			Stemp.push_back(dat.getVectorRules()[i].getHead().getVectorParams()[b].printS());

		}


		return Stemp;

	}

	Scheme setSchema(int & a, vector<Relation> & vecRel, Scheme & schema)

	{

		//cout << "in setSchema " << endl;

		Scheme temp;

		temp.pushSchema(schema);

		temp.pushSchema(vecRel[a].attributes);

		//temp.coutScheme();

		return temp;

	}

	void pushingsets(set<Tuple> & father, set<Tuple> & son)

	{

		for (Tuple t : son)

		{

			father.insert(t);

		}

	}

	Tuple pushingTuple(Tuple & father, Tuple & son)

	{

		Tuple t3;



		for (string s : son)

		{

			t3.push_back(s);

		}

		for (string s : father)

		{

			t3.push_back(s);

		}

		return t3;

	}


	bool canjoinQ(Scheme & schema, Tuple & t1, Tuple & t2, Tuple & temp)

	{

		//cout << "in can join Q and this is the schema " << endl;

		//schema.coutScheme();

		//cout << "schema size is " << schema.size() << endl;

		//cout << "tuple 1 size is " << t1.size() << endl;

		//cout << "tuple 2 size is " << t2.size() << endl;

		Tuple t3 = pushingTuple(t1, t2);

		//cout << "tuple 3 size is " << t3.size() << endl;

		//t3.coutTuple();

		for (int a = 0; a < schema.size(); a++)

		{

			for (int b = a + 1; b < schema.size(); b++)

			{


				if (schema[a] == schema[b])

				{
					//cout << "numbers are " << a << " VS " << b << endl;

					//cout << "schema " << schema[a] << " VS " << schema[b] << endl;

					//cout << "tuple " << t3[a] << " VS " << t3[b] << endl;

					if (t3[a] != t3[b])

					{

						//cout << "false" <<endl;

						return false;

					}

				}


			}

		}

		//cout << "Successfully adding to temp " <<endl;
		//t1.coutTuple();
		//cout << " and " ;
		//t2.coutTuple();

		//cout << endl;

		temp.pushTuple(t3);

		//temp.pushTuple(t2);

		return true;

	}

	Relation massiveSelection(unsigned int & i, vector<Relation> & v, vector<char> & rep)

	{

		//cout << "massiveSelection.. v.size is " << v.size() << " tuple.size is " << endl;

		Relation rel;

		set<Tuple>::iterator it;

		for (int a = 1; a < v.size(); a++)

		{

			for (Tuple t : v[a].getTuples())

			{

				for (int b = 0; b < t.size(); b++)

				{



				}

			}


		}


		return rel;

	}

	void cleaning(Tuple & x, Scheme & cleaned, set<Pset> & rep, bool & pass)

	{

		//cout << "in cleaning " << endl;

		int temp = 0;

		set<Pset>::iterator sp;

		Pset::iterator si;


		int a = 0;
		int b = 0;


		for (sp = rep.begin(); a < rep.size(); a++, sp++)

		{

			for (si = sp->begin(); b < sp->size(); b++, si++)

			{

				if (x[*si] != x[(*++si)])

				{

					pass = false;

					break;

				}



			}

			if (pass == false)

				break;



		}


	}



	vector<char> findingRep(Scheme schema)

	{

		//cout << "in finding rep " << endl;

		vector<char> vchar;

		set<char> schar;

		set<char>::iterator it;


		for (int a = 0; a < schema.size(); a++)

		{

			for (int b = a + 1; b < schema.size(); b++)

			{

				if (schema[a] == schema[b])

				{

					schar.insert(a);

					schar.insert(b);

				}

			}

		}


		for (it = schar.begin(); it != schar.end(); it++)

		{

			vchar.push_back(*it);

		}

		return vchar;

	}

	Relation Select(Relation & rel)

	{

		//cout << " In select " << endl;

		set<Tuple> tup = rel.getTuples();

		vector<Parameter> para;

		Parameter temp;

		//cout << " In select 1" << endl;



		for (int i = 0; i < rel.getAttributes().size(); i++)

		{

			//cout << "parameter is " << rel.getAttributes()[i] << endl;

			if (rel.getAttributes()[i][0] == '\'')

			{

				temp.setQuote(rel.getAttributes()[i]);

			}

			else

			{

				temp.setnoQuote(rel.getAttributes()[i]);

			}

			para.push_back(temp);

			temp.clear();

		}

		//rel.coutsetTuple(tup);

		//cout << "\n\n++++++++++++++++++++++++++++++++SELECT in " << rel.name << "\n" << endl;



		set<Tuple>::iterator it;

	label:

		for (unsigned int a = 0; a < para.size(); a++)

		{

			for (Tuple it : tup)

			{



				//cout << para.at(a).printS() << " VS " << it.at(a) << endl;

				if (para.at(a).printS() != it.at(a) && para.at(a).getBoolQuote() == true)

				{

					//cout << " ====Removed==== " << endl;

					tup.erase(it);

					goto label;

				}

			}

		}

		//coutsetTuple(tup);

		rel.setTupples(tup);

		return rel;

	}



	bool thereis1(Relation & rel)

	{

		bool there = false;

		for (auto a : Database)

		{

			if (a.first == rel.getName())

			{

				there = true;

			}

		}

		return there;

	}

	void Union(Relation & rel)

	{

		//cout << "in unionTuples " << endl;

		set<Tuple> t1;

		bool thereis = thereis1(rel);


		for (auto &a : Database)

		{

			//cout << "this is database name " << a.first << " this is new relation " << rel.getName() << endl;

			if (a.first == rel.getName() && thereis == true)

			{
				//cout << "relation existent so tuples added" << endl;

				//a.second.addTuples(rel.getTuples());

				for (Tuple T : a.second.getTuples())

				{

					t1.insert(T);

				}

				for (Tuple T : rel.getTuples())

				{

					t1.insert(T);

				}

				a.second.setTupples(t1);

				t1.clear();

				//cout << "This is set size " << a.second.getTuples().size() << endl;

			}

			else if (thereis == false)///////////////////new lines

			{

				//cout << "relation nonexistent so push entire relation " <<endl;

				Database.Push(rel.getName(), rel);

			}

		}



	}

	Relation Project(Relation & rel)

	{

		vector<Parameter> vecPar;

		Parameter par;

		for (int a = 0; a < rel.getRulesVar().size(); a++)

		{

			par.setnoQuote(rel.getRulesVar()[a]);

			vecPar.push_back(par);

			par.clear();

		}

		rel = rel.projectRules(vecPar);

		return rel;

	}

	Relation erasingDuplicates(Relation & rel)

	{

		//cout << "in erasingDuplicates... Rel.Tuples.size is " << rel.getTuples().size() << endl;

		set<Tuple> setTuple;

		vector<int> indexToErase;

		for (int a = 0; a < rel.getAttributes().size(); a++)

		{

			for (int b = a + 1; b < rel.getAttributes().size(); b++)

			{

				//cout << "Rel.Tuples.size is " << rel.getTuples().size() << endl;

				//cout << "Rel.getAttributes.size is " << rel.getAttributes().size() << endl;

				if (a < rel.getAttributes().size() - 1)

				{

					if (rel.getAttributes()[a] == rel.getAttributes()[b])

					{

						//cout << "pushing index " << b << endl;

						indexToErase.push_back(b);

					}

				}

			}

		}

		if (indexToErase.size() > 0)

		{

			rel = DuplicatesErased(indexToErase, rel);

		}

		return rel;

	}


	Relation DuplicatesErased(vector<int> & indexToErase, Relation & rel)

	{

		//cout << "in DuplicatesErased 1 indexToErase size is " << indexToErase.size() << endl;

		set<Tuple> temp;

		Tuple Ttemp;

		Scheme Stemp;

		Relation Trel;

		int a = 0;



		for (Tuple it : rel.getTuples())

		{

			//cout << "in DuplicatesErased 2" << endl;

			for (int i = 0; i < it.size(); i++)

			{

				//cout << "size is " <<  indexToErase.size() << " a is " << a << endl;

				if (i == indexToErase[a])

				{

					if (a < indexToErase.size() - 1)

						a++;

				}

				else

				{

					//cout << " tuples's para pushing back " << it[i] << endl;

					Ttemp.push_back(it[i]);

				}

			}

			temp.insert(Ttemp);

			Ttemp.clear();

			a = 0;

		}


		int b = 0;


		for (int i = 0; i < rel.getAttributes().size(); i++)

		{

			//cout << "in DuplicatesErased 5" << endl;

			if (i == indexToErase[b])

			{

				if (b < indexToErase.size() - 1)

					b++;

			}

			else

			{

				Stemp.push_back(rel.getAttributes()[i]);

			}

		}





		Trel.setName(rel.getName());

		Trel.setAttributes(Stemp);

		Trel.setTupples(temp);

		Trel.setVariables(rel.getVariables());

		Trel.setRulesVar(rel.getRulesVar());


		//cout << "temp.size is " << temp.size() << endl;

		return Trel;

	}


	Relation selectingTuplesFromNewRelation(Relation & rel)

	{

		//cout << "in selecting Tup from new Rel... Rel.Tuples.size is " << rel.getTuples().size() << endl;

		set<Tuple> setTuple;

		vector<string> rep;

		bool Brep = false;

		for (int a = 0; a < rel.getAttributes().size(); a++)

		{

			Brep = false;

			for (int c = 0; c < rep.size(); c++)

			{

				if (rep[c] == rel.getAttributes()[a]) Brep = true;

			}

			if (Brep == false)

			{

				for (int b = a + 1; b < rel.getAttributes().size(); b++)

				{

					//cout << "Rel.Tuples.size is " << rel.getTuples().size() << endl;

					if (a < rel.getAttributes().size() - 1)

					{

						if (rel.getAttributes()[a] == rel.getAttributes()[b])

						{



							//cout << "inside if temp VS b.. temp is " << temp << " [b] is " << rel.getAttributes()[b] << endl;

							setTuple = matchingTuples(a, b, rel.tuples);

							rel.setTupples(setTuple);

							rep.push_back(rel.getAttributes()[a]);


						}

					}

				}

			}

		}

		return rel;

	}

	set<Tuple> matchingTuples(int a, int b, set<Tuple> & tup)

	{

		//cout << "in matchinTuples a is " << a << " b is " << b << endl;

		set<Tuple> temp;

		set<Tuple>::iterator it;

		//for (it = tup.begin() ; it != tup.end() ; it++)

	label:

		for (Tuple it : tup)
		{

			//cout << "outside if... string[a] " << it->at(a) << " string[b] is " << it->at(b) << endl;

			if (it.at(a) != it.at(b))

			{

				//cout << "inside if... string[a] " << it->at(a) << " string[b] is " << it->at(b) << endl;

				tup.erase(it);

				goto label;

			}

		}


		//cout << "temp.size is " << temp.size() << endl;

		return tup;

	}

	Relation newRelation(vector<Relation> & vecRel, unsigned int & i)

	{

		//cout << "In new Relation " << " vecRel size is " << vecRel.size() << endl;

		Relation newRel;

		newRel.setName(dat.getVectorRules()[i].getHead().getName());



		for (int a = 0; a < vecRel.size(); a++)

		{

			//cout << "atributes from index " << a << endl;

			//vecRel[a].getAttributes().coutScheme();

			newRel.pushVecAttributes(vecRel[a].getAttributes());

		}

		set<Tuple> ss = combiningTuples(vecRel);

		newRel.setTupples(ss);

		Scheme Stemp;

		for (int b = 0; b < dat.getVectorRules()[i].getHead().getVectorParams().size(); b++)

		{

			Stemp.push_back(dat.getVectorRules()[i].getHead().getVectorParams()[b].printS());

		}

		newRel.setRulesVar(Stemp);

		return newRel;

	}

	set<Tuple> combiningTuples(vector<Relation> & v)

	{

		//cout << "in combining Tuples" << endl;

		set<Tuple> willEmpty;

		set<Tuple> willReturn;

		Tuple x;


		for (int a = 0; a < v.size(); a++)

		{

			for (Tuple t : v[a].getTuples())

			{

				if (willReturn.size() == 0)

				{

					willEmpty.insert(t);

				}

				else

				{

					for (Tuple t2 : willReturn)

					{

						x.pushTuple(t2);

						x.pushTuple(t);

						willEmpty.insert(x);

						x.clear();

					}

				}

			}

			willReturn = willEmpty;

			willEmpty.clear();
		}


		return willReturn;



	}

	vector<Relation> prediToRel(int i)

	{

		//cout << "In prediToRel " << endl;

		//cout << " rule name is " << dat.getVectorRules()[i].getHead().getName() << " and size of body is " << dat.getVectorRules()[i].getBody().size() << endl;

		Relation rel;

		vector<Relation> vecRel;

		for (int a = 0; a < dat.getVectorRules()[i].getBody().size(); a++)

		{

			rel.setName(dat.getVectorRules()[i].getBody()[a].getName());


			for (int b = 0; b < dat.getVectorRules()[i].getBody()[a].getVectorParams().size(); b++)

			{

				//cout << " for inside preditoRel " << dat.getVectorRules()[i].getBody()[a].getVectorParams()[b].printS() << endl;

				rel.pushAttributes(dat.getVectorRules()[i].getBody()[a].getVectorParams()[b].printS());

			}

			rel.setTupples(Database.getDataBase().at(dat.getVectorRules()[i].getBody()[a].getName()).getTuples());

			//cout << "after for, times " << i << " printing relation " << endl;

			//rel.coutRelation();

			vecRel.push_back(rel);

			rel.clear();

		}

		//cout << " cout vector of Relations" << endl;

		//for (int i = 0 ; i < vecRel.size() ; i++)

		//{

		//vecRel[i].coutRelation();

		//}

		return vecRel;

	}


	void readScheme()

	{

		for (unsigned int i = 0; i < dat.getVectorSchemes().size(); i++)

		{

			Relation temp;

			temp.setName(dat.getVectorSchemes()[i].getName());

			for (unsigned int a = 0; a < dat.getVectorSchemes()[i].getVectorParams().size(); a++)

			{

				temp.pushAttributes(dat.getVectorSchemes()[i].getVectorParams()[a].printS());

			}

			Database.Push(temp.getName(), temp);

		}

		//cout << "data base size " << Database.size() << endl;

		//Database.coutRelation();

	}


	void readFacts()

	{

		map<string, Relation>::iterator it;

		for (unsigned int i = 0; i < dat.getVectorFacts().size(); i++)

		{

			for (it = Database.begin(); it != Database.end(); it++)

			{

				if (dat.getVectorFacts()[i].getName() == it->first)

				{

					Tuple temp;

					for (unsigned int b = 0; b < dat.getVectorFacts()[i].getVectorParams().size(); b++)

					{

						temp.push_back(dat.getVectorFacts()[i].getVectorParams()[b].printS());

					}

					it->second.pushTuples(temp);

				}

			}

		}

		//cout << "data base size " << Database.size() << endl;

		//Database.coutRelation();

	}


	void evaluateQuery()

	{

		outRel = implementingSelect(outRel);

		//cout << "after select" << endl;

		//coutvectorRelation(outRel);



		outRel = implementingProject(outRel);

		//cout << "after project" << endl;

		//coutvectorRelation(outRel);




		outRel = implementingRename(outRel);

		//cout << "after rename" << endl;

		//coutvectorRelation(outRel);

	}



	vector<Relation> implementingSelect(vector<Relation> & vec)

	{

		//cout << "evaluating" << endl;

		map<string, Relation>::iterator it;

		Relation temp;

		for (unsigned int i = 0; i < dat.getVectorQueries().size(); i++)

		{

			for (it = Database.begin(); it != Database.end(); it++)

			{

				if (dat.getVectorQueries()[i].getName() == it->first)

				{
					//cout << "Query number " << i+1 << endl;

					temp = it->second.select(dat.getVectorQueries()[i].getVectorParams());

					//temp.coutRelation();

					vec.push_back(temp);

				}

			}

		}

		return vec;

	}



	vector<Relation> implementingProject(vector<Relation> & vec)

	{

		Relation temp;

		vector<Relation> rel;

		//cout << "in implementing project" << endl;

		for (unsigned int i = 0; i < vec.size(); i++)

		{

			//cout << "project i is " << i << " queries size is " << dat.getVectorQueries().size() << endl;

			temp = vec[i].project(dat.getVectorQueries()[i].getVectorParams());

			rel.push_back(temp);

		}

		return rel;

	}



	vector<Relation> implementingRename(vector<Relation> & temp)

	{

		Relation rel;

		vector<Relation> relvec;

		for (unsigned int i = 0; i < temp.size(); i++)

		{

			rel = temp[i].rename(dat.getVectorQueries()[i].getVectorParams());

			relvec.push_back(rel);

		}

		return relvec;

	}



	void coutvectorRelation(vector<Relation> vec)

	{

		for (unsigned int i = 0; i < vec.size(); i++)

		{

			vec[i].coutRelation();

			cout << endl;

		}

	}



	string printS()

	{

		//cout << "in printS " << endl;

		stringstream all;

		vector<Tuple> vec;

		//all << "Converged after " << FPcounter << " passes through the Rules." << endl;

		for (unsigned int i = 0; i < outRel.size(); i++)

		{

			all << outRel[i].getName() << "(";

			//cout << all.str() << endl;

			for (unsigned int a = 0; a < outRel[i].getAttributes().size(); a++)

			{



				all << outRel[i].getAttributes()[a];

				//cout << all.str() << endl;

				if (a < outRel[i].getAttributes().size() - 1)

					all << ",";

			}

			all << ")? ";

			if (outRel[i].getFound() == 0)

				all << "No\n";

			else

				all << "Yes(" << outRel[i].getFound() << ")\n";

			if (outRel[i].getVariables().size() != 0)

			{

				printS2(all, i);

			}

		}

		//cout << all.str() << endl;
		outRel.clear();

		FPcounter = 1;

		all << endl;

		return all.str();

	}

	void printS2(stringstream& all, unsigned int& i)

	{

		for (Tuple t : outRel[i].getTuples())

		{

			all << "  ";

			for (unsigned int a = 0; a < t.size(); a++)

			{

				if (a < outRel[i].getVariables().size())

					all << outRel[i].getVariables()[a] << "=" << t[a];

				if (a < outRel[i].getVariables().size() - 1)

					all << ", ";

			}

			all << "\n";

		}



	}







};







#endif /* INTERPRETER_H_ */
