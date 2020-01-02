//
// Created by yehonatan on 13/12/2019.
//

#include "laxer.h"
#include "fstream"
#include <list>
#include <stack>

using namespace std;
list<string>* split(string str, string token);
vector<string> removeSpace(vector<string> vec) {
	string temp;
	for (auto& s : vec) {
		temp = "";
		if (s[0] == '"') {
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
vector<string>* separateWhileCondition(string& line, string& s) {
    vector<string> tokens = {"==", "<=", ">=", "<", ">", "!="};
    vector<string>* str_array = new vector<string>();
    list<string>* temp;
    for (auto token :tokens) {
        temp = split(s, token);
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
vector<string> laxer::laxe(const char *file_name) {
    vector<string> str_array;
    ifstream f;
    f.open(file_name);
    if(!f.good()) {
        throw "cant open the file";
    }
    string line;
    vector<string>* temp;
    while (getline(f, line)) {
        string s = this->getWord(line, false);
        char c;
        bool flag = false;
        bool whileLine = false;
        while (line.length() > 0) {
            if (s != "") {
                while (s[0] == ' ' || s[0] == '\t') {
                    s = s.substr(1);
                    line = line.substr(1);
                    if (line.length() == 0) {
                        break;
                    }
                }
                if (s.length() > 2 && (s[0] != '\"')) {
                    temp = separateByToken(line, s, "->");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    } else {
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
            while (s[0] == ' ' || s[0] == '\t') {
                s = s.substr(1);
                line = line.substr(1);
                if (line.length() == 0) {
                    break;
                }
            }
            if (s.length() > 2 && (s[0] != '\"')) {
                temp = separateByToken(line, s, "->");
                if (temp->size() > 0) {
                    for (auto i : *temp) {
                        str_array.push_back(i);
                    }
                    delete temp;
                }
                else {
                    delete temp;
                    temp = separateByToken(line, s, "<-");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    }
                    delete temp;
                }
            } if (s.length() > 1 && (s[0] != '\"') && !whileLine) {
                    temp = separateByToken(line, s, "=");
                    if (temp->size() > 0) {
                        for (auto i : *temp) {
                            str_array.push_back(i);
                        }
                    }
                    delete temp;
            }
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
    str_array = removeSpace(str_array);
    return str_array;
}
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
string laxer::getWord(string s, bool flag) {
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