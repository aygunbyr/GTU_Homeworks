#include <iostream>
#include "organism.h"
#include "world.h"
using namespace std;

Organism::Organism() {
    x = 0;
    y = 0;
    breed_time = 0;
    is_moved = false;
    worldPtr = NULL;
}

Organism::Organism(World* earth, int x, int y) {
    this->x = x;
    this->y = y;
    breed_time = 0;
    is_moved = false;
    worldPtr = earth;
    earth->setCell(this, x, y);
}

Organism::~Organism() {}