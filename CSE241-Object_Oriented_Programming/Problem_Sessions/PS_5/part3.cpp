#include <iostream>
using namespace std;

class PrimeNumber {
    public:
    PrimeNumber() {
        prime = 1;
    }
    PrimeNumber(int p) {
        prime = p;
    }
    int getPrime() {return prime;}
    void setPrime(int num) {prime=num;}
    PrimeNumber& operator++ (); // prefix ++
    PrimeNumber operator++ (int number); // postfix ++
    PrimeNumber& operator-- (); // prefix --
    PrimeNumber operator-- (int number); // postfix --
    bool isPrimeNumber(int number);

    private:
    int prime;
};

PrimeNumber& PrimeNumber :: operator++()
{
    do
    {
        prime++;
    } while ( ! isPrimeNumber(prime) );
   
   return *this;
}

PrimeNumber PrimeNumber :: operator++(int)
{
   PrimeNumber temp = *this;
   ++*this;
   return temp;
}

PrimeNumber& PrimeNumber :: operator--()
{
    do
    {
        prime--;
    } while ( ! isPrimeNumber(prime) );
   
   return *this;
}

PrimeNumber PrimeNumber :: operator--(int)
{
   PrimeNumber temp = *this;
   ++*this;
   return temp;
}

bool PrimeNumber :: isPrimeNumber (int number)
{
    bool isPrime = true;
    int i;

    for(i=2; i<number; i++)
        if(number % i == 0)
            isPrime = false;

    return isPrime;
}

int main() {
    for (PrimeNumber a(2); a.getPrime() < 50; a++)
        cout << "Prime Number: " << a.getPrime() << endl;
    return 0;
}