//============================================================================
// Name        : cs236lab1.cpp
// Author      : Isai Mercado Oliveros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//sssssssssssssssss
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "Scanner.h"
#include "Parser.h"
#include "Token.h"
#include "DataLog.h"
#include "Interpreter.h"
#include "Graph.h"

using namespace std;





int main(int argc, char** argv)

{

// Getting input file from argv or by typing

	ifstream infile;

	infile.open(argv[1]);

	if (infile.fail() == true)

	{

		cout << "argv[1] incorrect file" << endl;

		infile.clear();

		string textfile;

		cout << "type textfile to open " << endl;

		cin >> textfile;

		infile.open(textfile.c_str());

	}

	if (infile.fail() == true) { cout << "incorrect file" << endl; infile.clear(); return 0;}








// Reading input file and converting it into a large string

	string intext;

	char c;

	while (infile.eof() == false)
	{

		c = infile.get();

		intext = intext + c;

	}
	infile.close();









// Project_1 Reads text and converts it into a vector of Tokens

	Scanner scannerMachine;

	scannerMachine.scan(intext);

	vector<Token> listTokens = scannerMachine.getVectorToken();

	//cout << scannerMachine.make_string()<< endl;









// Project_2 Reads a vector and separates it into more vectors by category in a DataLog Class

	Parser parserMachine;

	parserMachine.parse(listTokens);

	DataLog data = parserMachine.getDataLog();

	//cout << parserMachine.printS() << endl;








// Project_3 and 4 Reads DataLog Class and evaluates the Query

//	Interpreter interpreterMachine;
//
//	interpreterMachine.interprete(data);
//
//	cout <<endl<<endl<< interpreterMachine.printS();


	GraphDriver MachineGraph;

	MachineGraph.drive(data);

	cout << "outside 55" << endl;

	cout << MachineGraph.printS();





	ofstream out_file(argv[2]);

	out_file << MachineGraph.printS();



	return 0;

}



