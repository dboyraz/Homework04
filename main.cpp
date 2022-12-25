#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "User.h"
#include "TextTable.h"

using namespace std;

void readFromFile(unordered_map<string, string> &map, const string &fileName) {

    // Read from text file and put them as key-value pairs in a map
    ifstream paramFile;
    paramFile.open(fileName);
    string key;
    string value;

    while (paramFile >> key >> value) {
        map[key] = value;
    }

    paramFile.close();

}

void writeToFile(unordered_map<string, string> &map, const string &fileName) {

    // Write your key-value pairs in a map to text file
    ofstream paramFile;
    paramFile.open(fileName);

    for (auto const &[k, v]: map) {
        paramFile << k << " " << v << endl;
    }

    paramFile.close();

}

void addUser(unordered_map<string, string> &map, const string &fileName) {

    // 1 - Take input
    // 2 - Add to map
    // 3 - Write map to text file

    string u;
    string p;

    cout << "Registering new user.." << endl;
    cout << "Enter a username." << endl;
    cin >> u;
    cout << "Enter a password." << endl;
    cin >> p;

    map.insert({u, p});
    writeToFile(map, fileName);


}

void deleteUser(unordered_map<string, string> &map, const string &fileName) {


    // 1- Take input
    // 2- Delete it from map
    // 3- Rewrite file using map
    string u;
    cout << "Enter username you would like to delete" << endl;
    cin >> u;
    map.erase(u);
    writeToFile(map, fileName);

}

void printUsers(const unordered_map<string, string> &map) {

    // Generates a text table for user list using TextTable class
    TextTable t('-', '|', '+');

    t.add("Name");
    t.add("Password");
    t.endOfRow();

    for (auto const &[k, v]: map) {

        t.add(k);
        t.add(v);
        t.endOfRow();

    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;

}

void loginHandler(unordered_map<string, string> &map, const string &fileName) {

    int failedLoginCount{0}; // Counter for failed login
    User user;
    string uname;
    string pwd;

    // 1 - Take input
    // 2 - Read from text file(where you store your login info) into a map
    // 3 - Compare input against your map for login operation
    restart:
    cout << "Please enter your username." << endl;
    cin >> uname;
    rePassword:
    cout << "Please enter your password." << endl;
    cin >> pwd;

    user.setUserName(uname);
    user.setPassword(pwd);

    readFromFile(map, fileName);

    for (auto const &[k, v]: map) {

        // If the input matches a key-value pair in map, login success
        if (map.find(user.getUserName()) != map.end() && map[user.getUserName()] == user.getPassword()) {


            cout
                    << "-------------------------------------------------------------------------------------------------\n";
            cout << "-------------------------------- LOGIN SUCCESSFUL, WELCOME " << user.getUserName()
                 << " --------------------------------\n";
            cout
                    << "-------------------------------------------------------------------------------------------------\n";
            break;
        }
            //username is true but password is wrong
        else if (map.find(user.getUserName()) != map.end() &&
                 map[user.getUserName()] != user.getPassword()) {

            failedLoginCount++;
            if (failedLoginCount >= 3) {
                cout << "You have failed to enter your password 3 times, aborting the program!\n";
                exit(0);
            }

            cout << "Wrong password, tries left : " << 3 - failedLoginCount << "/3" << endl;
            goto rePassword;

        } else {
            cout << "Username not found, restarting login sequence...\n";
            goto restart;
        }


    }


}

void menuHandler(unordered_map<string, string> &map, const string &fileName) {

    head:
    char c{' '};
    cout << "Type a number to proceed." << endl;
    cout << "1 - List all Users." << endl;
    cout << "2 - Add a User." << endl;
    cout << "3 - Remove a User." << endl;
    cout << "4 - Logout " << endl;
    cout << "5 - Exit Program" << endl;

    cin >> c;

    switch (c) {
        case '1':
            cout << "Listing all users...\n";
            printUsers(map);
            cout << "Returning back to the menu...\n\n";
            goto head;
        case '2':
            addUser(map, fileName);
            cout << "User successfully added!\n";
            cout << "Returning back to the menu...\n\n";
            goto head;
        case '3':
            deleteUser(map, fileName);
            cout << "User successfully deleted!\n";
            cout << "Returning back to the menu...\n\n";
            goto head;
        case '4':
            cout << "Logging out...\n";
            loginHandler(map, fileName);
            menuHandler(map, fileName);
            break;
        case '5':
            cout << "Exiting program.\n";
            exit(0);
        default:
            cout << "default";
    }
}


int main() {

    unordered_map<string, string> userList;
    const string fileName = R"(C:\Users\deniz\users.txt)"; // Location of user list




    cout << "    ____             __   _                __          __     __  ___                                 \n"
            "   / __ \\____ ______/ /__(_)___  ____ _   / /   ____  / /_   /  |/  /___ _____  ____ _____ ____  _____\n"
            "  / /_/ / __ `/ ___/ //_/ / __ \\/ __ `/  / /   / __ \\/ __/  / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ ___/\n"
            " / ____/ /_/ / /  / ,< / / / / / /_/ /  / /___/ /_/ / /_   / /  / / /_/ / / / / /_/ / /_/ /  __/ /    \n"
            "/_/    \\__,_/_/  /_/|_/_/_/ /_/\\__, /  /_____/\\____/\\__/  /_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/     \n"
            "                              /____/                                               /____/             \n"
            "" << endl;


    loginHandler(userList, fileName);
    menuHandler(userList, fileName);


    return 0;
}
