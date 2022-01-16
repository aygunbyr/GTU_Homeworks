#include <iostream>
#include <cmath>
using namespace std;

class MyInteger {
  public:
  void setInteger(int value) {integer=value;}
  int getInteger() {return integer;}
  int operator [] (int position);

  private:
  int integer;
};

int MyInteger :: operator[] (int position) 
{
  int i, result;
  result = integer;
  if(integer > pow(10, position) - 1)
  {
    for(i=1; i<=position; i++)
    {
      result /= 10;
    }
    result = result % 10;
    return result;
  }
  else if(integer == 0 && position == 0)
    return 0;
  else
    return -1;
}

int main() {
  int i;
  MyInteger a;
  a.setInteger(564);
  cout << "TEST" << endl;
  cout << "Integer a is " << a.getInteger() << endl;
  for(i=0; i<4; i++)
  {
      cout << "Digit #" << i << " of number is " << a[i] << endl; 
  }


  return 0;
}