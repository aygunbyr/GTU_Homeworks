#include <iostream>
using namespace std;

class Vector2D {
    public:
    int getx() { return x;}
    int gety() { return y;}
    void setx(int value) {x=value;}
    void sety(int value) {y=value;}
    int operator * (Vector2D vb);

    private:
    int x, y;

};

int Vector2D :: operator * (Vector2D vb)
{
    return (x * vb.x)+(y *vb.y);
}

int main() {
    Vector2D a, b;
    int dot_product;
    a.setx(5);
    a.sety(1);
    b.setx(3);
    b.sety(2);
    dot_product = a*b;
    cout << "Vector A: " << a.getx() << "," << a.gety() << " and Vector B: " << b.getx() << "," << b.gety() << endl;
    cout << "Dot product of A and B is " << dot_product << endl;

    return 0;
}