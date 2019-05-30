#include"ShuntingYard.h"


using namespace std;

bool OperatorMapClass::isStackOperatorHigherPrecedence(char operatorChar, char operatorStackChar) {
	return((operatorMapObj.count(operatorStackChar))
		&&
		(operatorMapObj.at(operatorStackChar) > operatorMapObj.at(operatorChar)));
}//isStackOperatorHigherPrecedence()


OperatorMapClass  operatorMapObj;

string ShuntingYardClass::createPostFixFrom(string infixString) {

	string       outputString;
	stack <char> operatorStackObj;

	for (char token : infixString) {
		switch (token) {
		case '/':
		case '*':
		case '+':
		case '-':
			while ((!operatorStackObj.empty()) && (!operatorMapObj.isStackOperatorHigherPrecedence(token, operatorStackObj.top())) && (operatorStackObj.top() != '('))
			{
				outputString.push_back(operatorStackObj.top());
				operatorStackObj.pop();
			}
			operatorStackObj.push(token);
			// xxx insert code here
			/*

			while (the stack is not empty
			AND
			the top of the stack token is not a left parenthesis
			AND
			precedence of the current operator <= precedence of the top of the stack token
			)
			{
			Push back the stack top token to the output string
			Pop the stack top and discard it
			}//while-end

			Push the current operator token onto the stack
			*/
			break;
		case '(':                                                       // left parenthesis                   
																		// xxx insert code here
			operatorStackObj.push(token);
			// push this token on the stack
			break;
		case ')':
			// xxx insert code here                                                      // right parenthesis
			while ((!operatorStackObj.empty()) && (operatorStackObj.top() != '('))
			{
				outputString.push_back(operatorStackObj.top());
				operatorStackObj.pop();
			}
			operatorStackObj.pop();
			/*

			while (the stack is not empty AND the top stack token is not a left parenthesis)
			{
			Push back the stack top token to the output string
			}//while-end

			Pop the left parenthesis from the stack and discard it
			*/
			break;
		default:                                                        // operand                                                         
																		// xxx insert code here
			outputString.push_back(token);
			// push back the operand symbol to the output string 
			break;
		}//switch
	}//for

	 // xxx insert code here
	while ((!operatorStackObj.empty()))
	{
		outputString.push_back(operatorStackObj.top());
		operatorStackObj.pop();
	}
	/*
	while (the stack is not empty)
	{
	//Push back any remaining stack tokens to the output string
	}//while-end
	*/
	return(outputString);

}//postfix()	