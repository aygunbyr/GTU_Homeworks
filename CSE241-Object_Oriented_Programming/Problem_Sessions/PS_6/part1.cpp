#include <iostream>
using namespace std;

class Complex {
    public:
    Complex (double r, double ipart) {
        real = r;
        imaginary = ipart;
    }
    Complex(double realPart) {
        real = realPart;
        imaginary = 0;
    }
    Complex() {
        real = 0;
        imaginary = 0;
    }
    bool operator==(Complex c2);
    void operator<<(Complex c2);
    void operator>>(Complex c2);
    Complex operator+(Complex c2);
    Complex operator-(Complex c2);
    Complex operator*(Complex c2);
    void setReal(double r) { real=r; }
    void setImaginary(double i) {imaginary=i;}
    double getReal(){return real;}
    double getImaginary(){return imaginary;}

    private:
    double real;
    double imaginary;

};

bool Complex :: operator== (Complex c2) {
    if(real == c2.getReal() && imaginary == c2.getImaginary())
        return true;
    else
        return false;
}

void Complex :: operator<< (Complex c2) {
    c2.setImaginary(imaginary);
    c2.setReal(real);
}

void Complex :: operator>> (Complex c2) {
    real = c2.getReal();
    imaginary = c2.getImaginary();
}

Complex Complex :: operator+ (Complex c2) {
    Complex new_c;
    new_c.real = real + c2.getReal();
    new_c.imaginary = imaginary + c2.getImaginary();
    return new_c;
}

Complex Complex :: operator- (Complex c2) {
    Complex new_c;
    new_c.real = real - c2.getReal();
    new_c.imaginary = imaginary - c2.getImaginary();
    return new_c;
}

Complex Complex :: operator* (Complex c2) {
    Complex new_c;
    new_c.real = (real*c2.getReal()) - (imaginary*c2.getImaginary());
    new_c.imaginary = (real*c2.getImaginary()) + (imaginary*c2.getReal());
    return new_c;
}

int main() {
    const Complex i(0, 1);
    Complex a, b, result, input_complex;
    int input_num;

    cout << "TEST PROGRAM" << endl;

    cout << "Enter real part for complex number a: ";
    cin >> input_num;
    input_complex.setReal(input_num);

    cout << "Enter imaginary part for complex number a: ";
    cin >> input_num;
    input_complex.setImaginary(input_num);

    // Set a with overloaded input operator
    a >> input_complex;

    cout << "Enter real part for complex number b: ";
    cin >> input_num;
    input_complex.setReal(input_num);

    cout << "Enter imaginary part for complex number b: ";
    cin >> input_num;
    input_complex.setImaginary(input_num);

    // Set b with overloaded input operator
    b >> input_complex;

    cout << "a = " << a.getReal() << " + " << a.getImaginary() << "i" << endl;
    cout << "b = " << b.getReal() << " + " << b.getImaginary() << "i" << endl;

    result = a+b;
    cout << "a + b = " << result.getReal() << " + " << result.getImaginary() << "i" << endl;

    result = a-b;
    cout << "a - b = " << result.getReal() << " + " << result.getImaginary() << "i" << endl;

    result = a*b;
    cout << "a * b = " << result.getReal() << " + " << result.getImaginary() << "i" << endl;
  
}
