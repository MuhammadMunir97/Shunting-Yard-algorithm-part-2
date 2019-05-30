#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

class OperatorMapClass
{

private:
	typedef map<char, int>    OperatorPrecedenceMapType;
	OperatorPrecedenceMapType operatorMapObj;

public:
	OperatorMapClass() {
		operatorMapObj.insert(OperatorPrecedenceMapType::value_type('-', 4));
		operatorMapObj.insert(OperatorPrecedenceMapType::value_type('+', 3));
		operatorMapObj.insert(OperatorPrecedenceMapType::value_type('*', 2));
		operatorMapObj.insert(OperatorPrecedenceMapType::value_type('/', 1));
		// xxx insert code here to insert * and / in the map object
	}//OperatorMapClass ()
	bool isStackOperatorHigherPrecedence(char operatorChar, char operatorStackChar);

};//OperatorMapClass


class ShuntingYardClass 
{

public:
	string createPostFixFrom(string infixString);

};//ShuntingYardClass

