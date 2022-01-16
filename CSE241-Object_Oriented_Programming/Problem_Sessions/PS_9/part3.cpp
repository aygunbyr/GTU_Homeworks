#include <iostream>
#include <string>
using namespace std;

// Declaration of function prototypes
void reverse(char *str, int index_first, int index_last);
void reverse_string(string& str);

int main()
{
    // Test program
    string str;
    cout << "Enter your string: ";
    getline(cin, str);
    reverse_string(str);
    cout << "Reverse of your string is: " << str << endl;
    return 0;
}

void reverse(char * str, int index_first, int index_last)
{
    int i;
    char temp;
    // Iterative loop
    while(index_first < index_last)
    {
        temp = str[index_first];
        str[index_first] = str[index_last];
        str[index_last] = temp;
        index_first++;
        index_last--;
    }
}

void reverse_string(string& str){
    // Get size for use then as last index
    int size = str.size();

    // Call to recursive function
    reverse( &str[0], 0, size-1);
}