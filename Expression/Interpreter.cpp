//
// Created by yehonatan on 10/11/2019.
//

#include <list>
#include <queue>
#include <stack>
#include "Interpreter.h"
#include <iostream>
#include "ex1.h"

using namespace std;

Interpreter::Interpreter() {
    this->vars = new map<string, double>();
}

Interpreter::~Interpreter() {
    delete this->vars;
}

Expression *Interpreter::interpret(string exp) {
    queue<string> postfix;
    stack<char> operators;
    string uop = "+-";
    string op = "+-*/";
    string moreOp = "+-/*()";
    bool hasValBefore = false;
    for (int i = 0; i < exp.length(); i++) {
        if (op.find(exp[i]) != std::string::npos) {
            while (!operators.empty() && operators.top() != '(') {
                char leastOp = operators.top();
                while (moreOp.find(leastOp) == std::string::npos) {
                    string s = "";
                    s += leastOp;
                    postfix.push(s);
                    operators.pop();
                    if (operators.empty()) {
                        leastOp = '(';
                        break;
                    }
                    leastOp = operators.top();
                }
                if (leastOp == '(' || !isSmaller(leastOp, exp[i])) {
                    break;
                } else {
                    string s = "";
                    if (uop.find(operators.top()) == std::string::npos || hasValBefore) {
                        s += operators.top();
                    } else if (operators.top() == '-') {
                        s += '@';
                    } else if (operators.top() == '+') {
                        s += '$';
                    }
                    postfix.push(s);
                    operators.pop();
                }
            }
            char s;
            if (uop.find(exp[i]) == std::string::npos || hasValBefore) {
                s = exp[i];
            } else if (exp[i] == '-') {
                s = '@';
            } else if (exp[i] == '+') {
                s = '$';
            }
            operators.push(s);
        } else if (exp[i] == '(') {
            operators.push('(');
            hasValBefore = false;
        } else if (exp[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string s = "";
                s += operators.top();
                postfix.push(s);
                operators.pop();
            }
            if (operators.empty()) {
                throw "bad input";
            }
            operators.pop();
            hasValBefore = true;
        } else {
            string varOrVal = "";
            while (moreOp.find(exp[i]) == std::string::npos && i < exp.length()) {
                varOrVal += exp[i];
                i++;
            }
            if (isVal(varOrVal)) {
                postfix.push(varOrVal);
            } else if (isVar(varOrVal)) {
                if ((*this->vars).find(varOrVal) != (*this->vars).end()) {
                    postfix.push((varOrVal));
                } else {
                    throw "bad input";
                }
            } else {
                throw "bad input";
            }
            i--;
            hasValBefore = true;
        }

    }
    while (!operators.empty()) {
        string s = "";
        s += operators.top();
        postfix.push(s);
        operators.pop();
    }
    stack<Expression *> vals;
    string un = "@$";
    while (!postfix.empty()) {
        string s = postfix.front();
        postfix.pop();
        if (isVal(s)) {
            vals.push(new Value(stod(s)));
        } else if (isVar(s)) {
            vals.push(new Variable(s, this->vars->find(s)->second));
        } else if (un.find(s) != string::npos) {
            if (s == "@") {
                if (vals.empty()) {
                    throw "bad input";
                }
                Expression *e = vals.top();
                vals.pop();
                vals.push(new UMinus(e));
            } else if (s == "$") {
                if (vals.empty()) {
                    throw "bad input";
                }
                Expression *e = vals.top();
                vals.pop();
                vals.push(new UPlus(e));
            }
        } else {
            if (vals.empty()) {
                throw "bad input";
            }
            Expression *right = vals.top();
            vals.pop();
            if (vals.empty()) {
                throw "bad input";
            }
            Expression *left = vals.top();
            vals.pop();
            switch (s[0]) {
                case '+':
                    vals.push(new Plus(left, right));
                    break;
                case '-':
                    vals.push(new Minus(left, right));
                    break;
                case '*':
                    vals.push(new Mul(left, right));
                    break;
                case '/':
                    vals.push(new Div(left, right));
                    break;
                case '(':
                    throw "bad input";
            }
        }

    }

    return vals.

            top();

}

void Interpreter::setVariables(string vars) {
    list<string> *newVars = split(vars, ";");

    for (string s : *newVars) {
        if (s.find("=") == string::npos) {
            delete newVars;
            throw "bad input";
        }
        string var = s.substr(0, s.find("="));
        s.erase(0, s.find("=") + 1);
        string val = s;

        if (val.length() == 0 || !isVal(val)) {
            delete newVars;
            throw "bad input";
        }

        if (var.length() == 0 || !isVar(var)) {
            delete newVars;
            throw "bad input";
        }
        (*(this->vars))[var] = stod(val);
    }
    delete newVars;

}

bool Interpreter::isVal(string val) {
    bool hasDote = false;
    for (int i = 0; i < val.length(); i++) {
        if (((i > 0) || val[i] != '-' || val.length() == 1) && (val[i] < '0' || val[i] > '9') &&
            !(i > 0 && i < val.length() - 1
              && (val[i] == '.') && !hasDote)) {
            return false;
        } else if (val[i] == '.') {
            hasDote = true;
        }

    }
    return true;
}

bool Interpreter::isVar(string var) {
    if ((var[0] >= '0' && var[0] <= '9')) {
        return false;
    }
    for (int i = 0; i < var.length(); i++) {
        if ((var[i] < '0' || var[i] > '9') && (var[i] < 'A' || var[i] > 'Z')
            && (var[i] < 'a' || var[i] > 'z') && var[i] != '_') {
            return false;
        }
    }
    return true;
}

list<string> *Interpreter::split(string str, string token) {
    if (str[str.length() - 1] != token[0])
        str += token;
    list<string> *list = new std::list<string>();
    size_t pos = 0;
    while ((pos = str.find(token)) != std::string::npos) {
        list->push_back(str.substr(0, pos));
        str.erase(0, pos + token.length());
    }
    return list;
}

bool Interpreter::isSmaller(char o1, char &i) {
    switch (o1) {
        case '*':
        case '/':
        case '(':
            return false;
        case '+':
        case '-':
            switch (i) {
                case '*':
                case '/':
                    return true;
                case '+':
                case '-':
                    return false;
            }
    }
    return true;
}
