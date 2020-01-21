//
// Created by yehonatan on 20/01/2020.
//
#include <list>
#include <sys/socket.h>
#include "MyTestClientHandler.h"
#include <cstring>
#include <unistd.h>

using namespace std;
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
void MyTestClientHandler::handleClient(int &client_socket) {
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
            if (cm->isExist(s)) {
                string message = cm->get(s);
                message += '\n';
                send(client_socket, message.c_str(), message.length(), 0);
            } else {
                string message = solver->solve(s);
                message += '\n';
                send(client_socket, message.c_str(), message.length(), 0);
                cm->insert(s, message);
            }
        }
    }
    close(client_socket);

}

/**
 * search for \n in s
 */
bool MyTestClientHandler::hasPacket(string s) {
    for (int i =0; i< s.length(); ++i) {
        if (s[i] == '\n') {
            return true;
        }
    }
    return false;
}