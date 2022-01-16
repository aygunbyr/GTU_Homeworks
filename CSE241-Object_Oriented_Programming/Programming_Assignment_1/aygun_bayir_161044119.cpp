#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

bool is_number(string s);
bool is_repeating(string s);
int get_length(char arr[]);
int convert_to_integer(string s);
int generate_valid_number(int digits);
int count_matched(int secret_number, int guess_number);
int count_misplaced(int secret_number, int guess_number, int digits);

int main(int argc, char** argv) {
    string input1;
    int digits, guess, secret, turn_count = 0;
    char mode;
    srand(time(NULL));
    bool found, proper;
    proper=true;

    if(argv[1][0] == '-')
	    mode = argv[1][1];

    // Missing or undefined parameter
    if( argc != 3 )
    {
        cout << "E0" << endl;
        proper = false;
    }

    if(mode == 'r' || mode == 'R')
    {
        digits = convert_to_integer(argv[2]);
        secret = generate_valid_number(digits);
        if(digits > 9)
        {
            cout << "E0" << endl;
            proper = false;
        }
    } else if(mode == 'u' || mode == 'U')
    {
        if(is_repeating(argv[2])) {
            cout << "E0" << endl;
            proper = false;
        } else {
            secret = convert_to_integer(argv[2]);
            digits = get_length(argv[2]);
        }
    } else {
        cout << "E0" << endl;
        proper = false;
    }

    // If proper, it passed every error check.
    if(proper) {
        // Secret number has not found yet
        found = false;

        // Ask user till he/she found secret number
        while(secret != guess && turn_count < 100) {
            cin >> input1;
            if(is_number(input1) == true)
            {
                guess = convert_to_integer(input1);
            }
            if(is_number(input1) == false)
            {
                cout << "E2" << endl;
                proper = false;
            }
            else if(guess >= (int)pow(10,digits) || guess < (int)pow(10,digits-1))
            {
                cout << "E1" << endl;
                proper = false;
            }
            else if(digits <= 0 || is_repeating(input1)) {
                cout << "E0" << endl;
                proper = false;
            }

            turn_count++;
            if(secret == guess)
                found = true;
            if(found == false && proper)
                cout << count_matched(secret, guess) << " " << count_misplaced(secret, guess,  6) << endl;
        }
        // Check if secret number found or not
        if(found)
            cout << "FOUND " << turn_count << endl;
        if(turn_count == 100 && found == false)
            cout << "FAILED" << endl;
    }

    return 0;
    
}

bool is_number(string s) {
    // Check whether is input an integer
    int i;
    bool flag=true;
    for(i=0; i<s.length(); i++)
        if(s[i] < '0' || s[i] > '9')
            flag = false;
    return flag;
}

bool is_repeating(string s) {
    // Check is a number repeating
    int i, j;
    bool flag=false;
    for(i=1; i<s.length(); i++)
        for(j=0; j<i; j++)
            if(s[i] == s[j])
                flag = true;
    return flag;
}

int get_length(char arr[])
{
    int i;
    for(i=0; arr[i] != '\0'; i++);
    return i;
}

int convert_to_integer(string s) {
    int i, number, length;
    number=0;
    length = s.length();
    for(i=s.length()-1; i>=0; i--)
        number = number + ( (int) pow(10,length-i-1) ) * (s[i] - 48);
    return number;
}

int generate_valid_number(int digits)
{
    // Generate a valid secret number
    int number=0, base_number;
    string s;
    do {
        base_number = (int) pow(10, digits-1);
        number = (rand() % (1+base_number*10-base_number)) + base_number;
        s = to_string(number);
    } while(number == 0 || is_repeating(s) || is_number(s) == false);
    return number;
}

int count_matched(int secret_number, int guess_number)
{
    // Count all matched digits between secret number and guess number
    int matched = 0;
    while(secret_number > 0)
    {
        if(secret_number % 10 == guess_number % 10)
            matched++;
        secret_number /= 10;
        guess_number /= 10;
    }
    return matched;
}

int count_misplaced(int secret_number, int guess_number, int digits)
{
    int i, j, secret_number_elements[digits], guess_number_elements[digits], misplaced=0;
    bool found_in_other;

    // Fill arrays of elements 
    for(i=digits-1; i>=0; i--)
    {
        secret_number_elements[i] = secret_number % 10;
        guess_number_elements[i] = guess_number % 10;
        secret_number /= 10;
        guess_number /= 10;
    }

    // Count misplaced elements
    for(i=0; i<digits; i++)
    {
        found_in_other=false;
        for(j=0; j<digits; j++)
            if(secret_number_elements[i] == guess_number_elements[j])
                found_in_other=true;
        if(found_in_other && secret_number_elements[i] != guess_number_elements[i])
            misplaced++;
    }

    return misplaced;
}
