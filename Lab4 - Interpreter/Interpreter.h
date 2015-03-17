/*
 * graph.h
 *
 *  Created on: Aug 7, 2014
 *      Author: misaie
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <string>
#include <map>
#include "Interpreter.h"
#include "DataLog.h"
#include <sstream>
#include "Rule.h"
#include "Predicate.h"

using namespace std;




class Node

{

private:



public:

	string ID;

	bool mark;

	int postOrder;

	set<string> adjacents;

	Rule rule;

	Predicate query;

	void setQuery(Predicate x)

	{

		query = x;

	}

	Predicate getQuery()

	{

		return query;

	}

	Rule getRule()

	{

		return rule;

	}

	void setRule(Rule x)

	{

		rule = x;

	}

	void clear()

	{

		ID.clear();

		adjacents.clear();

		mark = false;

		postOrder = 0;

	}

	void pushNode(string x)

	{

		adjacents.insert(x);

	}

	int getpostOrder()

	{

		return postOrder;

	}

	bool getmark()

	{

		return mark;

	}

	set<string> getadjacents()

	{

		return adjacents;

	}

	string getID() const

	{

		return ID;

	}

	void setpostOrder(int x)

	{

		postOrder = x;

	}

	void setmark(bool x)

	{

		mark = x;

	}

	void setadjacents(set<string> x)

	{

		adjacents = x;

	}

	void setID(string x)

	{

		ID = x;

	}


	Node()

	{

		mark = false;

		postOrder = 0;

	}

	~Node()

	{



	}

};

//bool operator < (const Node & lhs, const Node & rhs)
//{
// Put code here to return true/false value based on whether lhs is less than rhs
//    if ( lhs.getname() < rhs.getname() )
//        return true;
//    if ( rhs.getname() < lhs.getname() )
//        return false;
//    if ( lhs.getname() < rhs.getname() )
//        return true;
//    if ( rhs.getname() < lhs.getname() )
//        return false;
//    return false;
//
//
//}




class Graph
{

private:





public:

	map<string, Node> graph;

	map<string, Node>::iterator it;

	map<int, Node> evaluator;

	vector<pair<string, string>> backward;

	map<string, set<string>> back;

	string printSback()

	{

		stringstream ss;

		ss << "  Backward Edges" << endl;

		for (auto b : back)

		{

			ss << "    " << b.first << ": ";

			for (string s : b.second)

			{

				ss << s << " ";

			}

			ss << endl;

		}

		ss << endl;

		return ss.str();

	}

	void backClear()

	{

		back.clear();

	}

	void backwardClear()

	{

		backward.clear();

	}

	string prinSBackward()

	{

		stringstream ss;

		ss << "  Backward Edges" << endl;

		for (auto b : backward)

		{

			ss << "    " << b.first << ": " << b.second << endl;

		}

		ss << endl;

		return ss.str();

	}

	void clearFlags()

	{

		for (it = graph.begin(); it != graph.end(); it++)

		{

			it->second.setmark(false);

		}

	}

	void clearpostNum()

	{

		for (it = graph.begin(); it != graph.end(); it++)

		{

			it->second.setpostOrder(0);

		}

	}

	string printSevaluationOrder()

	{

		stringstream ss;

		ss << "  Rule Evaluation Order" << endl;

		for (auto e : evaluator)

		{

			if (e.second.getID()[0] != 'Q')

				ss << "    " << e.second.getID() << endl;

		}

		return ss.str();

	}


	string printSPostNumber()

	{

		stringstream ss;

		ss << "  Postorder Numbers" << endl;

		for (auto g : graph)

		{

			if (g.second.getpostOrder() != 0)

			{

				ss << "    " << g.second.getID() << ": " << g.second.getpostOrder() << endl;

			}

		}

		ss << endl;

		return ss.str();
	}


	string printSDependencyGraph()

	{

		stringstream ss;

		ss << "Dependency Graph " << endl;

		for (auto g : graph)

		{

			ss << "  " << g.first << ": ";

			for (auto s : g.second.getadjacents())

			{

				ss << s << " ";

			}

			ss << endl;

		}

		return ss.str();


	}

	Graph()

	{



	}

	~Graph()

	{



	}

	map<string, Node> getgraph()

	{

		return graph;

	}

	void addNode(string ID, Node x)

	{

		graph[ID] = x;

	}

	void setgraph(map<string, Node> x)

	{

		graph = x;

	}

	void insert(string x, Node y)

	{

		graph[x] = y;

	}

};



class GraphDriver

{

private:


	Graph graph;

	vector<pair<Predicate, string>> query;

	stringstream output;

	DataLog data;

	DataLog permanent;

	DataLog changing;

	int rulesadded;

	int Mpost;



public:

	Interpreter interpreterMachine;



	GraphDriver()

	{

		rulesadded = 0;

		Mpost = 0;

	}

	~GraphDriver()

	{



	}

	void drive(DataLog x)

	{

		this->data = x;

		this->permanent.setVectorSchemes(x.getVectorSchemes());

		this->permanent.setVectorFacts(x.getVectorFacts());

		interpreterMachine.setDatalog(permanent);

		Graph temp;

		makingDependencyGraph();

		for (auto Q : query)

		{
			//cout << "rule is " << Q.first << endl;

			stringstream all;

			all << Q.first.getName() << "(";

			//cout << all.str() << endl;

			for (unsigned int a = 0; a < Q.first.getVectorParams().size(); a++)

			{



				all << Q.first.getVectorParams()[a].printS();

				//cout << all.str() << endl;

				if (a < Q.first.getVectorParams().size() - 1)

					all << ",";

			}

			all << ")? " << endl << endl;

			output << all.str();

			depthSearch(Q.second);

			output << graph.printSPostNumber();

			evaluating();

			graph.clearpostNum();

			graph.clearFlags();

			Mpost = 0;

			graph.evaluator.clear();

			graph.backwardClear();

			graph.backClear();





		}

		//cout << graph.printSPostNumber() << endl;


	}

	void evaluating()

	{

		output << graph.printSevaluationOrder() << endl;

		findbackedges();

		//cout << graph.prinSBackward();

		output << graph.printSback();



		output << "  Rule Evaluation" << endl;

		//if (interpreterMachine.getDataLog().getVectorRules().size() != 0)

		if (graph.back.size() != 0)

			evaluatingRules1();

		else

			evaluatingRules2();

		output << endl;

		evaluateQuery();

		output << interpreterMachine.printS();


		//interpreterMachine.interprete(changing);

		//cout << interpreterMachine.printS() << endl;

	}

	void evaluateQuery()

	{

		for (auto n : graph.evaluator)

		{

			if (n.second.getID()[0] == 'Q')

			{

				//cout << "from graph evaQuery " << n.second.getQuery().printS() << endl;

				interpreterMachine.evaQuery(n.second.getQuery());

			}

		}


	}

	void evaluatingRules2()

	{

		for (auto n : graph.evaluator)

		{

			if (n.second.getID()[0] == 'R')

			{

				output << "    " << n.second.getRule().printS() << endl;

				interpreterMachine.evaRule(n.second.getRule());

				//evaluatingRules1(n.second.getRule());

			}

		}

	}

	void evaluatingRules1()
	{

		int initial = interpreterMachine.getdatabase().getInitialSize();

		//cout << rule.printS() << endl;

		//interpreterMachine.evaRule(rule);


		for (auto n : graph.evaluator)

		{

			if (n.second.getID()[0] == 'R')

			{

				output << "    " << n.second.getRule().printS() << endl;

				interpreterMachine.evaRule(n.second.getRule());

			}

		}

		int later = interpreterMachine.getdatabase().getlaterSize();

		if (initial != later)

		{

			evaluatingRules1();

		}



	}

	void findbackedges()

	{

		//cout << "in finding backward edges " << endl;

		map<int, Node>::iterator it;

		set<string>::iterator ss;

		map<string, Node>::iterator st;



		for (it = graph.evaluator.begin(); it != graph.evaluator.end(); it++)
		{

			for (ss = it->second.adjacents.begin(); ss != it->second.adjacents.end(); ss++)

			{

				for (st = graph.graph.begin(); st != graph.graph.end(); st++)

				{

					if (*ss == st->first)

					{

						if (st->second.getpostOrder() >= it->second.getpostOrder())

						{

							//cout << " backward edge " << st->second.getID() << " " << it->second.getID() << endl;

							//graph.backward.push_back(make_pair(it->second.getID(),st->second.getID()));

							graph.back[it->second.getID()].insert(st->second.getID());

						}

					}

				}

			}

		}

	}

	void depthSearch(string next)

	{

		//cout << "in depth search function..next is " << next << endl;

		map<string, Node>::iterator it;



		for (it = graph.graph.begin(); it != graph.graph.end(); it++)

		{

			//cout << "this is the node " << (*it).first << endl;

			if (next == it->first && it->second.getmark() == false)

			{

				// cout << it->first << " graph Matched name " << next << endl;

				// cout << " adjacent size is " << it->second.adjacents.size() << endl;

				it->second.setmark(true);

				for (auto n : it->second.adjacents)

				{

					// cout << "going through adjacent rules " << n << endl;

					depthSearch(n);

				}



				Mpost++;

				it->second.setpostOrder(Mpost);

				//if (next[0] != 'Q')

				graph.evaluator[Mpost] = it->second;

				//cout << "post order is " << it->second.getpostOrder() << endl;

			}


		}





	}

	map<string, Predicate> qnames(map<string, Predicate> Qnames)

	{

		for (unsigned int a = 0; a < data.getVectorQueries().size(); a++)

		{

			stringstream ss;

			ss << "Q" << a + 1;

			//revenue.push_back(std::make_pair("string",map[i].second));

			Qnames[ss.str()] = data.getVectorQueries()[a];

			query.push_back(make_pair(data.getVectorQueries()[a], ss.str()));

			data.getVectorQueries()[a].setID(ss.str());

			//data.getVectorQueries()[a].ID = ss.str();

		}

		return Qnames;

	}

	map<string, Rule> rnames(map<string, Rule> Rnames)

	{

		for (unsigned int a = 0; a < data.getVectorRules().size(); a++)

		{
			stringstream ss;

			ss << "R" << a + 1;

			Rnames[ss.str()] = data.getVectorRules()[a];

			data.getVectorRules()[a].setID(ss.str());

			//data.getVectorRules()[a].ID = ss.str();

		}

		return Rnames;

	}


	void makingDependencyGraph()

	{

		map<string, Predicate> Qnames;

		map<string, Rule> Rnames;

		map<string, vector<string>> table;

		Qnames = qnames(Qnames);


		//        for (unsigned int a = 0 ; a < data.getVectorQueries().size() ; a++)
		//
		//        {
		//
		//            stringstream ss;
		//
		//            ss << "Q" << a+1;
		//
		//            //revenue.push_back(std::make_pair("string",map[i].second));
		//
		//            Qnames[ss.str()] = data.getVectorQueries()[a];
		//
		//            query.push_back(make_pair(data.getVectorQueries()[a],ss.str()));
		//
		//            data.getVectorQueries()[a].setID(ss.str());
		//
		//            //data.getVectorQueries()[a].ID = ss.str();
		//
		//        }


		Rnames = rnames(Rnames);

		//        for (unsigned int a = 0 ; a < data.getVectorRules().size() ; a++)
		//
		//        {
		//            stringstream ss;
		//
		//            ss << "R" << a+1;
		//
		//            Rnames[ss.str()] = data.getVectorRules()[a];
		//
		//            data.getVectorRules()[a].setID(ss.str());
		//
		//            //data.getVectorRules()[a].ID = ss.str();
		//
		//        }



		for (auto m : Rnames)

		{

			table[m.second.getHead().getName()].push_back(m.first);

		}


		for (auto n : Qnames)

		{

			Node temp;

			temp.setID(n.first);

			temp.setQuery(n.second);

			for (auto t : table)

			{

				if (n.second.getName() == t.first)
				{

					for (auto v : t.second)

					{

						temp.pushNode(v);



					}

				}

			}

			graph.insert(n.first, temp);


		}



		//        for (auto n : Rnames)
		//
		//        {
		//
		//           // cout << "Rname " << n.second.getHead().getName() << endl;
		//
		//            Node temp;
		//
		//            temp.setID(n.first);
		//
		//            temp.setRule(n.second);
		//
		//            for (auto p : n.second.getBody())
		//
		//            {
		//
		//                //cout << "body " << p.getName() << endl;
		//
		//
		//
		//                //cout << "name n " << n.first << endl;
		//
		//                for (auto t : table)
		//
		//                {
		//
		//                    //cout << "body VS table " << p.getName() << " " << t.first << endl;
		//
		//                    if (p.getName() == t.first)
		//                    {
		//
		//                        //cout << "matched " << endl;
		//
		//                        for (auto v : t.second)
		//
		//                        {
		//
		//                            //cout << "pushing " << v << " " ;
		//
		//                            temp.pushNode(v);
		//
		//
		//
		//                        }
		//
		//                       // cout << endl;
		//
		//                    }
		//
		//
		//
		//                }
		//
		//
		//
		//            }
		//
		//            graph.insert(n.first, temp);
		//
		//        }

		graphing(Rnames, table);

		output << graph.printSDependencyGraph() << endl;


	}

	void graphing(map<string, Rule> Rnames, map<string, vector<string>> table)

	{

		for (auto n : Rnames)

		{

			// cout << "Rname " << n.second.getHead().getName() << endl;

			Node temp;

			temp.setID(n.first);

			temp.setRule(n.second);

			for (auto p : n.second.getBody())

			{

				//cout << "body " << p.getName() << endl;



				//cout << "name n " << n.first << endl;

				for (auto t : table)

				{

					//cout << "body VS table " << p.getName() << " " << t.first << endl;

					if (p.getName() == t.first)
					{

						//cout << "matched " << endl;

						for (auto v : t.second)

						{

							//cout << "pushing " << v << " " ;

							temp.pushNode(v);



						}

						// cout << endl;

					}



				}



			}

			graph.insert(n.first, temp);

		}

	}

	string printS()

	{

		return output.str();

	}





};


#endif /* GRAPH_H_ */



