#include <iostream>
#include <string>
#include "security.h"
#include "UserSecurity.h"
#include "AdministratorSecurity.h"
using namespace std;


int main() {
    string username, password;
    UserSecurity user;
    cout << "USER LOGIN" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    user.Login(username, password);
    user.welcome();

    AdministratorSecurity admin;
    cout << "ADMIN LOGIN" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    admin.Login(username, password);
    admin.welcome();
    
}