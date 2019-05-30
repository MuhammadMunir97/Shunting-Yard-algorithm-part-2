//=========================================================//
/*
Course      : Programming Fundamentals III (C++) COSC 2336
Name        : Muhammad S Munir
Assignment  : Lab Assiggnment 5
Chapter		: N/A
Page		: N/A
Title       : Binary Expression tree
*/
//==========================================================//

// ShuntBETTemplateSol.cpp : Defines the entry point for the console application.

// ShuntingYardPostFixBETSol.cpp : Defines the entry point for the console application.

// Construction of an expression tree uses a stack to process the tree nodes
//
// To construct an expression tree: 
//
//    Loop through the postfix expression for every token
//       If the token is an operand 
//         Put the token into a node and push the operand token node onto the stack
//	     Else
//         token is an operator 
//         Place/Pop 2 token nodes from stack, make these tokens the children for the current token node
//
//    When loop is done processing tokens, 
//    The stack node will be the root


// Code that you need to develop is marked in areas with xxx

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

string inputFileNameStr = "expressions.txt";                  // Defaults in solution folder

class OperatorMapClass {

private:
    typedef map<char, int>    OperatorPrecedenceMapType;
    OperatorPrecedenceMapType operatorMapObj;

public:

    OperatorMapClass() {

        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('-', 1));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('+', 2));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('*', 3));
        operatorMapObj.insert(OperatorPrecedenceMapType::value_type('/', 4));

    }//OperatorMapClass ()

    bool isStackOperatorHigherPrecedence(char operatorChar, char operatorStackChar) {
        return((operatorMapObj.count(operatorStackChar))
            &&
            (operatorMapObj.at(operatorStackChar) > operatorMapObj.at(operatorChar)));
    }//isStackOperatorHigherPrecedence()

    bool  isOperator(char token) {
        if (operatorMapObj.count(token))
            return (true);
        else
            return(false);
    }//isOperator()

};//OperatorMapClass

OperatorMapClass  operatorMapObj;

class ShuntingYardClass {

public:

    string createPostFixFrom(string infixString) {

        string       outputString;
        stack <char> operatorStackObj;

        for (char token : infixString) {
            switch (token) {

            case '/': case '*': case '+': case '-':
                while (
                    (!operatorStackObj.empty())
                    &&
                    (operatorStackObj.top() != '(')
                    &&
                    (operatorMapObj.isStackOperatorHigherPrecedence(token, operatorStackObj.top()))
                    )
                {
                    outputString.push_back(operatorStackObj.top());
                    operatorStackObj.pop();
                }//while

                operatorStackObj.push(token);
                break;

            case '(':                                                       // left parenthesis                   
                operatorStackObj.push(token);
                break;

            case ')':                                                       // right parenthesis
                while ((operatorStackObj.top()) != '(') {
                    outputString.push_back(operatorStackObj.top());
                    operatorStackObj.pop();
                }
                operatorStackObj.pop();
                break;

            default:                                                        //operand
                outputString.push_back(token);
                break;

            }//switch
        }//for

        while (!operatorStackObj.empty()) {                                // if any remainng operators on the stack, pop all push back to the output
            outputString.push_back(operatorStackObj.top());
            operatorStackObj.pop();
        }

        return(outputString);

    }//postfix()	

};//ShuntingYardClass

class TreeNodeClass {

public:
    TreeNodeClass  *left;
    char            value;
    TreeNodeClass  *right;

};//TreeNodeClass

TreeNodeClass* BuildNewNodeObjPtrMethod(char value) {

    TreeNodeClass *newNodePtr = new TreeNodeClass;
    // xxx set the new node pointer value to the char parameter 
	newNodePtr->value = value;
    // xxx set newNodePtr left and right branch pointers to null
	newNodePtr->left = NULL;
	newNodePtr->right = NULL;
    return newNodePtr;
};


TreeNodeClass * ConstructBET(string postFixStr) {
    stack<TreeNodeClass *>      parseStack;
    TreeNodeClass              *newNodePtr;
    OperatorMapClass            OperatorMapObj;

    // Process each character of the post-fix expression
    for (char token : postFixStr) {
        // xxx Form a new node pointer by submitting a token to BuildNewNodeObjPtrMethod and assigning return to new node pointer
		newNodePtr = BuildNewNodeObjPtrMethod(token);
        if (OperatorMapObj.isOperator(token)) {
            // xxx
            // xxx Operator,  Put/Remove top 2 from parse stack nodes into a new node pointer sub tree as right, left children
			newNodePtr->right = parseStack.top();
			parseStack.pop();
			newNodePtr->left = parseStack.top();
			parseStack.pop();
            // xxx Put this new node pointer sub tree node to the parseStack
			parseStack.push(newNodePtr);
        }
        else {
            // operand, put new node pointer onto parse stack
            parseStack.push(newNodePtr);
        }
    }

    //  Place remaininng sub tree root node on stack into tree
    newNodePtr = parseStack.top(); parseStack.pop();

    return newNodePtr;
}


string buildString;

void preorder(TreeNodeClass *treeNode) {
 
    // xxx insert code here
    // if not null transverse: 
	if (treeNode == NULL)
		return;

	// buildString output using current tree node value
	buildString += treeNode->value;
	// do recursive left
	preorder(treeNode->left);
	// do recursive right 
	preorder(treeNode->right);
	
}

bool areParensRequired(TreeNodeClass *treeNode, char value) {
    OperatorMapClass operatorMapObj;
    if (operatorMapObj.isOperator(value)
        &&
        operatorMapObj.isOperator(treeNode->value)
        &&
        operatorMapObj.isStackOperatorHigherPrecedence(treeNode->value, value)) {
          buildString += '(';
		  return true;
	}
    return false;
}

void inorder(TreeNodeClass *treeNode) {
    bool parensRequired = false;

    // if not null then transverse
    if (treeNode) {

        // xxx 
        // check if parentheses are required, save state
		parensRequired = areParensRequired(treeNode->left, treeNode->value);
        // recurse transverse left
		inorder(treeNode->left);
		//cout << "bool value=" << parensRequired << endl;
		//system("pause");
        // if parentheses are required append closed ) to the build string
		if (parensRequired != false)
		{
			buildString += ')';
		}
        buildString += treeNode->value;

		parensRequired = areParensRequired(treeNode->right, treeNode->value);

        // xxx 
        //recurse transverse right
		inorder(treeNode->right);
		
        // if parentheses are required append closed ) to the build string
		if (parensRequired != false)
		{
			buildString += ')';
		};
    }//if
}

void postorder(TreeNodeClass *treeNode) {
 
    // xxx insert code here
    // if not null transverse: 
	if (treeNode == NULL)
		return;
    // do recursive left
	postorder(treeNode->left);
    // do recursive right 
	postorder(treeNode->right);
    // buildString output using current tree node value
	buildString.push_back(treeNode->value);
    
}


int main() {

    ifstream          inputFileStreamObj;

    inputFileStreamObj.open(inputFileNameStr, ios::in);
    if (inputFileStreamObj.fail()) {
        cout << "File could not be opened !" << endl;
        return (EXIT_FAILURE);
    }//if

    string            infixExpressionStr,
                      postfixExpressionStr;
    const bool        EOF_ENCOUNTERED = false,
                      MORE_DATA_TO_READ = true;

    ShuntingYardClass shuntingYardObj;

    system("cls");

    while (getline(inputFileStreamObj, infixExpressionStr) ? MORE_DATA_TO_READ : EOF_ENCOUNTERED) {

        cout << "InFix   Expression : " << infixExpressionStr << endl;
        postfixExpressionStr = shuntingYardObj.createPostFixFrom(infixExpressionStr);
        cout << "PostFix Expression : " << postfixExpressionStr << endl << endl;

        TreeNodeClass * expressionTreeRootPtr = ConstructBET(postfixExpressionStr);
		system("pause");
        //xxx initialize build string, start a preorder transversal
		buildString.clear();
		preorder(expressionTreeRootPtr);
        cout << "Tree  pre-order expression is " << endl << buildString << endl << endl;
		system("pause");
        //xxx initialize build string, start an inorder transversal
		buildString.clear();
		inorder(expressionTreeRootPtr);
        cout << "Tree   in-order expression is " << endl << buildString << endl << endl;
		system("pause");
        ////xxx initialize build string, start an inorder transversal
		buildString.clear();
		postorder(expressionTreeRootPtr);
        cout << "Tree post-order expression is " << endl << buildString << endl << endl;

        cout << endl << endl;

    };//while

    inputFileStreamObj.close();

    system("pause");

    return EXIT_SUCCESS;

}//main()



