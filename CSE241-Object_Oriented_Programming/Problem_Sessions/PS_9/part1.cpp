#include <iostream>
using namespace std;

// Recursive helper function for a single parameter fibonacci function
int fibonacci_helper(int fibonacci_index, int fibonacci, int previous)
{
    if(fibonacci_index==0)
        return fibonacci;
    else
        fibonacci = fibonacci_helper(--fibonacci_index, fibonacci+previous, fibonacci);
    return fibonacci;
}

// Single parameter fibonacci function
int fibonacci(int n) {
    int fibonacci;
    fibonacci = fibonacci_helper(n, 1, 0);
    return fibonacci;
}

int main() {
    int i;
    // Test program
    cout << "First ten Fibonacci numbers:" << endl;

    for(i=0; i<10; i++)
        cout << "F" << i << "= " << fibonacci(i) << endl;
    
    return 0;
}