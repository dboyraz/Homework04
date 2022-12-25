//
// Created by deniz on 20-Dec-22.
//
#include <string>

#ifndef HOMEWORK04_USER_H
#define HOMEWORK04_USER_H
using namespace std;


class User {
private:
    string userName;
    string password;

public:
    User() {}

    User(string u, string p) {
        userName = u;
        password = p;
    }

    void setUserName(string userName);

    void setPassword(string password);

    string getUserName() { return userName; }

    string getPassword() { return password; }


};


#endif //HOMEWORK04_USER_H
