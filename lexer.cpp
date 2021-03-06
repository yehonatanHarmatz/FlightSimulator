//
// Created by yehonatan on 13/12/2019.
//

#include "lexer.h"
#include "fstream"
#include <list>
#include <stack>

using namespace std;
list<string>* split(string str, string token);
/***
 * remove space from expressions
 */
vector<string> removeSpace(vector<string> vec) {
	string temp;
	for (auto& s : vec) {
		temp = "";
		//check if not string
		if (s[0] == '\"') {
			continue;
		}
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == ' ') {
				continue;
			}
			temp += s[i];
		}
		s = temp;
	}
    return vec;
}
/**
 *
 * @param line from fly.txt to separate
 * @param s strin that help
 * @param token by who are we separting
 * @return the separated line parts
 */
vector<string>* separateByToken(string& line, string& s, string token) {
    vector<string>* str_array = new vector<string>();
    list<string>* temp = split(s, token);
    if (temp->size() > 1) {
        if (temp->front() != "") {
            str_array->push_back(temp->front());
        }
        str_array->push_back(token);
        line = line.substr(temp->front().length() + token.length());
        temp->pop_front();
        s = temp->front();
    }
    delete temp;
    return str_array;
}
/**
 * separte codition line
 * @param line the line
 * @param s help to separte
 * @return the separated line parts
 */
vector<string>* separateWhileCondition(string& line, string& s) {
    vector<string> tokens = {"==", "<=", ">=", "<", ">", "!="};
    vector<string>* str_array = new vector<string>();
    list<string>* temp;
    for (auto token :tokens) {
        temp = split(s, token);
        ///check if the condition is the current token
        if (temp->size() > 1) {
            if (temp->front() != "") {
                str_array->push_back(temp->front());
            }
            str_array->push_back(token);
            line = line.substr(temp->front().length() + token.length());
            temp->pop_front();
            s = temp->front();
            delete temp;
            break;
        }
        delete temp;
    }
    string a = s;
    if (a[a.length() - 1] == '{') {
        a = a.substr(0, a.length() - 1);
        str_array->push_back(a);
        line = line.substr(a.length());
        s = "{";
    }
    return str_array;
}
/**
 * the function that create vector of strings from the file
 * @param file_name
 * @return the vector of strings
 */
vector<string> lexer::laxe(const char *file_name) {
    vector<string> str_array;
    ifstream f;
    ///open the file to read
    f.open(file_name);
    if(!f.good()) {
        throw "cant open the file";
    }
    string line;
    vector<string>* temp;
    ///work on each line saperatly
    while (getline(f, line)) {
        string s = this->getWord(line, false);
        char c;
        bool flag = false;
        bool whileLine = false;
        while (line.length() > 0) {
            if (s != "") {
                ///remove tabs and spaces
                while (s[0] == ' ' || s[0] == '\t') {
                    s = s.substr(1);
                    line = line.substr(1);
                    if (line.length() == 0) {
                        break;
                    }
                }
                ///separate by ->
                if (s.length() > 2 && (s[0] != '\"')) {
                    temp = separateByToken(line, s, "->");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    } else {
                        ///separate by <-
                        delete temp;
                        temp = separateByToken(line, s, "<-");
                        if (temp->size() > 0) {
                            for (auto i : *temp) {
                                str_array.push_back(i);
                            }
                        }
                        delete temp;
                    }
                }
                ///separate by =
                if (s.length() > 1 && (s[0] != '\"') && !whileLine) {
                    temp = separateByToken(line, s, "=");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    }
                    delete temp;
                } if (s != "") {
                    str_array.push_back(s);
                }
            }
            ///flags about the line
            if (line[s.length()] == '(') {
                flag = true;
            } else if (line[s.length()] == ')'){
                flag = false;
            } else if (s == "=") {
                flag = true;
            } else if (s == "while" || s == "if") {
                whileLine = true;
                flag = true;
            }
            if (s.length() == line.length()) {
                break;
            }
            line = line.substr(s.length() + 1);
            s = this->getWord(line, flag);
            while (s == "") {
                //flag = true;
                line = line.substr(1);
                c = line[0];
                s += c;
                s = this->getWord(line, flag);
            }
            ///remove tabs and spaces
            while (s[0] == ' ' || s[0] == '\t') {
                s = s.substr(1);
                line = line.substr(1);
                if (line.length() == 0) {
                    break;
                }
            }
            ///separate by ->
            if (s.length() > 2 && (s[0] != '\"')) {
                temp = separateByToken(line, s, "->");
                if (temp->size() > 0) {
                    for (auto i : *temp) {
                        str_array.push_back(i);
                    }
                    delete temp;
                }
                else {
                    ///separate by <-
                    delete temp;
                    temp = separateByToken(line, s, "<-");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    }
                    delete temp;
                }
                ///separate by =
            } if (s.length() > 1 && (s[0] != '\"') && !whileLine) {
                    temp = separateByToken(line, s, "=");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    }
                    delete temp;
            }
            ///separate condition line
            if (whileLine) {
                temp = separateWhileCondition(line, s);
                if (temp->size() > 0) {
                    for (auto i : *temp) {
                        str_array.push_back(i);
                    }
                }
                delete temp;
            }
        }
    }
    f.close();
    ///remove spaces
    str_array = removeSpace(str_array);
    return str_array;
}
/**
 * split function
 * @param str
 * @param token
 * @return
 */
list<string>* split(string str, string token) {
    list<string> *list = new std::list<string>();
    size_t pos = 0;
    while ((pos = str.find(token)) != std::string::npos) {
        list->push_back(str.substr(0, pos));
        str.erase(0, pos + token.length());
    }
    list->push_back(str);
    return list;
}
/**
 * get the next separated word from the line
 * @param s
 * @param flag
 * @return
 */
string lexer::getWord(string s, bool flag) {
    char c = s[0];
    int i = 0;
    string word = "";
    string stop = "() ,";
    bool isString = false;
    stack<char> stk = stack<char>();
    if (flag || c == '=') {
        stop = ",";
    }
    if (c == '\"') {
        stop = "";
        isString = true;
    }
    while (stop.find(c) == string::npos && ((i+1) < s.length())) {
        ///check if leagal statment
        if (c == '(') {
            stk.push('a');
        } else if (c == ')') {
            if (stk.empty()) {
                stop = "() ,";
                break;
            } else {
                stk.pop();
            }
        } else if (c == '=' && !isString) {
            stop = ",";
        }
        word += c;
        c = s[++i];
        if (c == '\"' && isString) {
            break;
        }
    }

    if (stop.find(c) == string::npos) {
        if (c == ')') {
            if (!stk.empty()) {
                word += c;
            }
        } else {
            word += c;
        }
    }
    return word;
}