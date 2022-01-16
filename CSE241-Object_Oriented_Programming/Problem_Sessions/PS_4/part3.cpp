#include <iostream>
using namespace std;

class Point {
    public:
    void rotate();
    void move(int moveX, int moveY);
    void setX(int inpx) { x=inpx; }
    void setY(int inpy) { y=inpy; }
    const int getX() { return x; }
    const int getY() { return y; }

    private:
    int x;
    int y;
};

void Point::rotate() {
    // It rotates point 90 degrees around clockwise
    int tempX, tempY;
    tempX=x;
    tempY=y;

    y = tempX;
    x = tempY * -1;
}

void Point::move(int moveX, int moveY) {
    // It moves point by an amount
    x = x + moveX;
    y = y + moveY;
}

int main() {
    Point myPoint;

    return 0;
}