using namespace std;
class UserSecurity:public Security {
    public:
    UserSecurity(){username=""; password="";}
    UserSecurity(string user, string pw){username=user; password=pw;}
    bool Login(string username, string password);
    void welcome();
};

bool UserSecurity::Login(string user, string pw) {
    username=user;
    password=pw;
    if(validate(username, password) == 1 || validate(username, password) == 2)
            return true;
    else
        return false;
}

void UserSecurity::welcome(){
    if(validate(username, password) == 1)
        cout << "Welcome Administrator!" << endl;
    else if(validate(username, password) == 2)
        cout << "Welcome " << username << "!" << endl;
    else
        cout << "Login failed!" << endl;
}