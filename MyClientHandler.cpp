//
// Created by yehonatan on 28/01/2020.
//

#include "MyClientHandler.h"
//
// Created by yehonatan on 20/01/2020.
//
#include <list>
#include <sys/socket.h>
#include "MyTestClientHandler.h"
#include "searchable_table.h"
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

void MyClientHandler::handleClient(int &client_socket) {
    int sizeOfMatrix = -1;
    int line = 0;
    vector<vector<int>> table;
    pair<int, int> start;
    pair<int, int> end;
    const int size = 1024;
    char buffer[size] = {0};
    bool flag = true;
    string left = "";
    string s = left;
    left = "";
    while (s != "end") {
        flag = true;
        /**
         * recive packets from the client till we arrived \n
         */
        s = left;
        left = "";
        while (flag) {
            if (!hasPacket(s)) {
                recv(client_socket, buffer, size, 0);
            } else {
                list<string> *l = split(s, "\n");
                s = l->front();
                left = l->back();
                flag = false;
                delete l;
            }
            for (int i = 0; i < size; ++i) {
                if (buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '\r' && flag) {
                    s += buffer[i];
                } else if (buffer[i] == '\n' && flag) {
                    flag = false;
                } else if (!flag && buffer[i] != '\0' && buffer[i] != '\r') {
                    left += buffer[i];
                }
            }
            memset(buffer, 0, size);
        }
        if (s != "end") {
            list<string>* temp = split(s, ",");
            if (sizeOfMatrix == -1) {
                sizeOfMatrix = temp->size();
            }
            if (line < sizeOfMatrix) {
                for (int i = 0; i < sizeOfMatrix; ++i) {
                    table.at(line).at(i) = atoi(temp->front().c_str());
                    temp->pop_front();
                }
            }
            else if (line == sizeOfMatrix) {
                start = pInt(atoi(temp->front().c_str()), atoi(temp->back().c_str()));
            } else {
                end = pInt(atoi(temp->front().c_str()), atoi(temp->back().c_str()));
            }
            delete temp;
        }
        /// s = end so we solve and return the solution
        else {
            SearchableTable problem = SearchableTable(table, start, end);
            if (cm->isExist(to_string(problem.hash()))) {
                string message = cm->get(s);
                message += '\n';
                send(client_socket, message.c_str(), message.length(), 0);
            } else {
                string message = solver->solve(problem);
                message += '\n';
                send(client_socket, message.c_str(), message.length(), 0);
                cm->insert(to_string(problem.hash()), message);
            }
        }
    }
    //close(client_socket);

}

/**
 * search for \n in s
 */
bool MyClientHandler::hasPacket(string s) {
    for (int i =0; i< s.length(); ++i) {
        if (s[i] == '\n') {
            return true;
        }
    }
    return false;
}