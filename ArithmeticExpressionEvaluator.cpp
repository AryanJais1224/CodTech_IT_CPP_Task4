#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

// Define precedence of operators
int getPrecedence(char symbol) {
    if(symbol == '^') return 3;
    if(symbol == '*' || symbol == '/') return 2;
    if(symbol == '+' || symbol == '-') return 1;
    return 0;
}

// Check if character is an operator
bool isMathOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

// Convert infix to postfix using Shunting Yard algorithm
string convertInfixToPostfix(const string& infixExpr) {
    stack<char> operatorStack;
    string postfixExpr;

    for(char ch : infixExpr) {
        if(isspace(ch)) continue;

        if(isdigit(ch)) {
            postfixExpr += ch;
        }
        else if(ch == '(') {
            operatorStack.push(ch);
        }
        else if(ch == ')') {
            while(!operatorStack.empty() && operatorStack.top() != '(') {
                postfixExpr += ' ';
                postfixExpr += operatorStack.top();
                operatorStack.pop();
            }
            if(!operatorStack.empty()) operatorStack.pop(); // Pop '('
        }
        else if(isMathOperator(ch)) {
            postfixExpr += ' ';
            while(!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(ch)) {
                postfixExpr += operatorStack.top();
                postfixExpr += ' ';
                operatorStack.pop();
            }
            operatorStack.push(ch);
        }
    }

    while(!operatorStack.empty()) {
        postfixExpr += ' ';
        postfixExpr += operatorStack.top();
        operatorStack.pop();
    }

    return postfixExpr;
}

// Evaluate a postfix expression
int evaluatePostfixExpression(const string& postfixExpr) {
    stack<int> valueStack;
    string tempNum = "";

    for(char ch : postfixExpr) {
        if(ch == ' ') {
            if(!tempNum.empty()) {
                valueStack.push(stoi(tempNum));
                tempNum.clear();
            }
        }
        else if(isdigit(ch)) {
            tempNum += ch;
        }
        else if(isMathOperator(ch)) {
            int val2 = valueStack.top(); valueStack.pop();
            int val1 = valueStack.top(); valueStack.pop();
            switch(ch) {
                case '+': valueStack.push(val1 + val2); break;
                case '-': valueStack.push(val1 - val2); break;
                case '*': valueStack.push(val1 * val2); break;
                case '/': valueStack.push(val1 / val2); break;
                case '^': valueStack.push(pow(val1, val2)); break;
            }
        }
    }

    return valueStack.top();
}

int main() {
    cout << "Presenting a compiler to parse arithmetic expressions and evaluate them using BODMAS" << endl << endl;
    string userInput;
    cout << "Enter arithmetic expression: ";
    getline(cin, userInput);

    string postfixResult = convertInfixToPostfix(userInput);
    int finalValue = evaluatePostfixExpression(postfixResult);

    cout << "Evaluated Result: " << finalValue << endl;

    return 0;
}
