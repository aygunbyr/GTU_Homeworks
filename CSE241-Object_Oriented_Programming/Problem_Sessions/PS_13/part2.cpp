#include <iostream>
using namespace std;

class Account {
    private:
        double balance;
    public:
        Account() {
            balance=0;
        }
        Account(double initialDeposit) {
            balance = initialDeposit;
        }
        double getBalance(){return balance;}// returns new balance or -1 if error
        double deposit(double amount){
            try {
                if(amount>0)
                    balance += amount;
                else
                    throw 101;
            }
            catch(int x) {
                cout << "Error code: " << x << endl;
            }
            return balance;
        }
        double withdraw(double amount){
            try {
                if(amount>balance || amount<0)
                    throw 102;
                else
                    balance -= amount;
            }
            catch(int x) {
                cout << "Error code: " << x << endl;
            }
            return balance;
        }
};

int main() {
    Account myAccount(50);
    double deposit, withdraw;
    cout << "Your balance: " << myAccount.getBalance() << endl;

    cout << "Enter amount of withdraw: ";
    cin >> withdraw;
    myAccount.withdraw(withdraw);
    cout << "Your new balance: " << myAccount.getBalance() << endl;

    cout << "Enter amount of withdraw: ";
    cin >> withdraw;
    myAccount.withdraw(withdraw);
    cout << "Your new balance: " << myAccount.getBalance() << endl;

    cout << "Enter amount of deposit: ";
    cin >> deposit;
    myAccount.deposit(deposit);
    cout << "Your new balance: " << myAccount.getBalance() << endl;

    cout << "Enter amount of deposit: ";
    cin >> deposit;
    myAccount.deposit(deposit);
    cout << "Your new balance: " << myAccount.getBalance() << endl;


    return 0;
}

