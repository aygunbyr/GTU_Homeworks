using namespace std;
class AdministratorSecurity:public Security {
    public:
    AdministratorSecurity(){username=""; password="";}
    AdministratorSecurity(string user, string pw){username=user; password=pw;}
    bool Login(string username, string password);
    void welcome();
};

bool AdministratorSecurity::Login(string user, string pw) {
    username=user;
    password=pw;
    if(validate(username, password) == 1)
        return true;
    else
        return false;
}

void AdministratorSecurity::welcome(){
    if(validate(username, password) == 1)
        cout << "Welcome Administrator!" << endl;
    else
        cout << "Login failed!" << endl;
}