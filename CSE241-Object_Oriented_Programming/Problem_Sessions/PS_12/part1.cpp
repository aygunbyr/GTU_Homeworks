#include <iostream>
using namespace std;

template<typename T>
void absolute(T x, T y, T* absx, T* absy) {
    if(x >= 0)
        *absx = x;
    else
        *absx = 0-x;
    if(y >= 0)
        *absy = y;
    else
        *absy = 0-y;
}

int main() {
    int x, y, absx, absy;
    double d_x, d_y, d_absx, d_absy;
    float f_x, f_y, f_absx, f_absy;

    cout << "Test for Integer numbers" << endl;
    cout << "Enter integer x:";
    cin >> x;
    cout << "Enter integer y:";
    cin >> y;
    absolute(x, y, &absx, &absy);
    cout << "Absolute value of x: " << absx << endl;
    cout << "Absolute value of y: " << absy << endl;

    cout << "\nTest for double type numbers" << endl;
    cout << "Enter double x:";
    cin >> d_x;
    cout << "Enter double y:";
    cin >> d_y;
    absolute(d_x, d_y, &d_absx, &d_absy);
    cout << "Absolute value of x: " << d_absx << endl;
    cout << "Absolute value of y: " << d_absy << endl;

    cout << "\nTest for float type numbers" << endl;
    cout << "Enter float x: ";
    cin >> f_x;
    cout << "Enter float y: ";
    cin >> f_y;
    absolute(f_x, f_y, &f_absx, &f_absy);
    cout << "Absolute value of x: " << f_absx << endl;
    cout << "Absolute value of y: " << f_absy << endl;


    return 0;
}
