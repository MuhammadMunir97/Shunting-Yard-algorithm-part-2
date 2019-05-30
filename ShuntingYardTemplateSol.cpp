//=========================================================//
/*
Course      : Programming Fundamentals III (C++) COSC 2336
Name        : Muhammad S Munir
Assignment  : Lab Assiggnment 4
Chapter		: N/A
Page		: N/A
Title       : Shunting Yard Algorithm
*/
//==========================================================//

// ShuntingYardTemplateSol.cpp : Defines the entry point for the console application.
#include"ShuntingYard.h"

using namespace std;

string inputFileNameStr = "expressions.txt";                  // Default location in solution folder



int main() {

    ifstream          inputFileStreamObj;

    inputFileStreamObj.open(inputFileNameStr, ios::in);
    if (inputFileStreamObj.fail()) {
        cout << "File could not be opened !" << endl;
        return (EXIT_FAILURE);
    }//if

    string            infixExpressionStr,
                      postfixExpressionStr;
    const bool        EOF_ENCOUNTERED   = false,
                      MORE_DATA_TO_READ = true;

    ShuntingYardClass shuntingYardObj;

    system("cls");
    while (getline(inputFileStreamObj, infixExpressionStr) ? MORE_DATA_TO_READ : EOF_ENCOUNTERED) {   
        cout << "InFix   Expression : " << infixExpressionStr << endl;
        postfixExpressionStr = shuntingYardObj.createPostFixFrom(infixExpressionStr);
        cout << "PostFix Expression : " << postfixExpressionStr << endl << endl;
		system("pause");
		system("cls");
    };//while
	system("cls");
	cout << "Input File ended" << endl;
    system("pause");
    inputFileStreamObj.close();
	system("cls");
	cout << "Input File Closed" << endl;

    return EXIT_SUCCESS;

}//main()

