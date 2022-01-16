#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class CharPair {
    public:
    CharPair(){
        size=10;
        for(int i=0; i<10;i++)
            arr[i] = '#';
    }
    CharPair(int sz) {
        size=sz;
        for(int i=0; i<sz; i++)
            arr[i] = '#';
    }
    int getSize() {return size;}
    char& operator[](int index);

    private:
        char arr[100];
        int size;
};


int main() {
    int sz, num, i;
    string str_input;

    cout << "Enter the size of array:";
    cin >> sz;

    CharPair cp(sz);

    cout << "Enter " << sz << " characters to fill array:\n";
    getline(cin >> ws, str_input);

    for(i=0; i<sz; i++)
        cp[i] = str_input[i];

    cout << "Your full content of array is: " << endl;
    for(i=0; i<sz; i++)
        cout << cp[i];

    cout << "\nEnter an index number to access a character in array:";
    cin >> num;
    cout << "Character in index you entered is: " << cp[num] << endl;


    return 0;
}

// Uses iostream and cstdlib
char& CharPair::operator[](int index)
{
    if(index<0||index>=size)
    {
        cout << "Illegal index value.\n";
        exit(1);
    }
    else
    {
        return arr[index];
    }
}
