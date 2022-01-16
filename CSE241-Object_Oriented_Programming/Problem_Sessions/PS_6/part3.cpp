#include <iostream>
using namespace std;

class Rational {
    public:
    Rational(int num, int den) {
        numerator = num;
        denominator = den;
    }
    Rational(int wholeNumber) {
        numerator = wholeNumber;
        denominator = 1;
    }
    Rational() {
        numerator = 0;
        denominator = 1;
    }
    int getNumerator() {return numerator;}
    int getDenominator() {return denominator;}
    double getFraction() {return fraction;}
    void setNumerator(int num) {numerator = num;}
    void setDenominator(int deno) {denominator = deno;}
    void calculateFraction() {fraction = static_cast<double>(numerator) / static_cast<double>(denominator);}
    bool operator < (Rational secondRational);
    bool operator > (Rational secondRational);
    bool operator == (Rational secondRational);
    bool operator <= (Rational secondRational);
    bool operator >= (Rational secondRational);
    Rational operator + (Rational secondRational);
    Rational operator - (Rational secondRational);
    Rational operator * (Rational secondRational);
    Rational operator / (Rational secondRational);

    private:
    int numerator;
    int denominator;
    double fraction;
};

Rational Rational :: operator + (Rational secondRational)
{
    int first_denominator, first_numerator, second_denominator, second_numerator, this_numerator, this_denominator;
    Rational ret;

    // Get numerators and denominators
    first_denominator = denominator;
    first_numerator = numerator;
    second_denominator = secondRational.getDenominator();
    second_numerator = secondRational.getNumerator();

    // Calculate numerator and denominator
    ret.setNumerator(first_numerator * second_denominator + second_numerator * first_denominator);
    ret.setDenominator(first_denominator*second_denominator);

    return ret;
}

Rational Rational :: operator - (Rational secondRational)
{
    int first_denominator, first_numerator, second_denominator, second_numerator, this_numerator, this_denominator;
    Rational ret;

    // Get numerators and denominators
    first_denominator = denominator;
    first_numerator = numerator;
    second_denominator = secondRational.getDenominator();
    second_numerator = secondRational.getNumerator();

    // Calculate numerator and denominator
    ret.setNumerator(first_numerator * second_denominator - second_numerator * first_denominator);
    ret.setDenominator(first_denominator*second_denominator);

    return ret;
}

Rational Rational :: operator * (Rational secondRational)
{
    int first_denominator, first_numerator, second_denominator, second_numerator, this_numerator, this_denominator;
    Rational ret;

    // Get numerators and denominators
    first_denominator = denominator;
    first_numerator = numerator;
    second_denominator = secondRational.getDenominator();
    second_numerator = secondRational.getNumerator();

    // Calculate numerator and denominator
    ret.setNumerator((first_numerator * second_denominator) * (second_numerator * first_denominator));
    ret.setDenominator(first_denominator*second_denominator);

    return ret;
}

Rational Rational :: operator / (Rational secondRational)
{
    int first_denominator, first_numerator, second_denominator, second_numerator, this_numerator, this_denominator, temp;
    Rational ret;

    // Get numerators and denominators
    first_denominator = denominator;
    first_numerator = numerator;
    second_denominator = secondRational.getDenominator();
    second_numerator = secondRational.getNumerator();

    // Reverse second rational number
    temp = second_numerator;
    second_numerator = second_denominator;
    second_denominator = temp;

    // Multiply after reversing that is equal to divide
    ret.setNumerator((first_numerator * second_denominator) * (second_numerator * first_denominator));
    ret.setDenominator(first_denominator*second_denominator);

    return ret;
}

bool Rational :: operator < (Rational secondRational)
{
    double fraction, second_fr;
    fraction = static_cast<double>(numerator)/static_cast<double>(denominator);
    second_fr = static_cast<double>(secondRational.getNumerator()) / static_cast<double>(secondRational.getDenominator());

    if(fraction < second_fr)
        return true;
    else
        return false;
}

bool Rational :: operator > (Rational secondRational)
{
    double fraction, second_fr;
    fraction = static_cast<double>(numerator)/static_cast<double>(denominator);
    second_fr = static_cast<double>(secondRational.getNumerator()) / static_cast<double>(secondRational.getDenominator());

    if(fraction > second_fr)
        return true;
    else
        return false;
}

bool Rational :: operator == (Rational secondRational)
{
    double fraction, second_fr;
    fraction = static_cast<double>(numerator)/static_cast<double>(denominator);
    second_fr = static_cast<double>(secondRational.getNumerator()) / static_cast<double>(secondRational.getDenominator());

    if(fraction == second_fr)
        return true;
    else
        return false;
}

bool Rational :: operator <= (Rational secondRational)
{
    double fraction, second_fr;
    fraction = static_cast<double>(numerator)/static_cast<double>(denominator);
    second_fr = static_cast<double>(secondRational.getNumerator()) / static_cast<double>(secondRational.getDenominator());

    if(fraction <= second_fr)
        return true;
    else
        return false;
}

bool Rational :: operator >= (Rational secondRational)
{
    double fraction, second_fr;
    fraction = static_cast<double>(numerator)/static_cast<double>(denominator);
    second_fr = static_cast<double>(secondRational.getNumerator()) / static_cast<double>(secondRational.getDenominator());

    if(fraction >= second_fr)
        return true;
    else
        return false;
}

int main() {
    Rational x(2,4);
    Rational y(5,3);
    Rational result;
    int inputval;

    cout << "TEST PROGRAM" << endl;

    cout << "Enter x's numerator: ";
    cin >> inputval;
    x.setNumerator(inputval);
    cout << "Enter x's denominator: ";
    cin >> inputval;
    x.setDenominator(inputval);
    cout << "Enter y's numerator: ";
    cin >> inputval;
    y.setNumerator(inputval);
    cout << "Enter y's denominator: ";
    cin >> inputval;
    y.setDenominator(inputval);
    

    cout << "x = " << x.getNumerator() << "/" << x.getDenominator() << endl;
    x.calculateFraction();
    cout.precision(3);
    cout << "x = " << x.getFraction() << endl;
    cout << "y = " << y.getNumerator() << "/" << y.getDenominator() << endl;
    y.calculateFraction();
    cout.precision(3);
    cout << "y = " << y.getFraction() << endl;
    result = x+y;
    cout << "x + y = " << result.getNumerator() << "/" << result.getDenominator() << endl;
    result = x-y;
    cout << "x - y = " << result.getNumerator() << "/" << result.getDenominator() << endl;
    result = x*y;
    cout << "x * y = " << result.getNumerator() << "/" << result.getDenominator() << endl;
    result = x/y;
    cout << "x / y = " << result.getNumerator() << "/" << result.getDenominator() << endl;

    if(x==y)
        cout << "x is equal to y" << endl;
    else if(x<y)
        cout << "x is less than y" << endl;
    else if(x>y)
        cout << "x is bigger than y" << endl;

    if(x<=y)
        cout << "x is less or equal to y" << endl;
    if(x>=y)
        cout << "x is bigger or equal to y" << endl;


}
