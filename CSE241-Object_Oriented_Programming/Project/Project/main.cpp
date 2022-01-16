#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
using namespace std;


int main() {
    srand(time(NULL));
    World dunya;
    string str;
    bool loop=true;

    while (loop) {
        dunya.printWorld();
        dunya.tick();
        cout << "Press ENTER for next stage... " << endl;
        getline(cin, str);
    }
    return 0;
}