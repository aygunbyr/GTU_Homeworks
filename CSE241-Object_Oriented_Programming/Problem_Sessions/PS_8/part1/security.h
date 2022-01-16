using namespace std;
class Security
{
    protected:
    string username;
    string password;
    public:
    Security(){
        username="";
        password="";
    }
    Security(string user, string pw) {
        username=user;
        password=pw;
    }
    void setUsername(string user){username=user;}
    void setPassword(string pw){password=pw;}
    string getUsername(){return username;}
    string getPassword(){return password;}
    static int validate(string username, string password);
};
// This subroutine hard-codes valid users and is not
// considered a secure practice.
// It returns 0 if the credentials are invalid,
// 1 if valid user, and
// 2 if valid administrator
int Security::validate(string username, string password)
{
if ((username=="abbott") && (password=="monday")) return 1;
if ((username=="costello") && (password=="tuesday")) return 2;
return 0;
}