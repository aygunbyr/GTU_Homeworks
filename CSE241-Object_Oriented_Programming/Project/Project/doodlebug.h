#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include <iostream>
#include "world.h"
#include "organism.h"

class Doodlebug : public Organism {
    friend class World;
    private:
        int starve_time;
        bool poison_eaten;
        int moves_after_poison;
    public:
        Doodlebug();
        Doodlebug(World* earth, int x, int y);
        int getType() {return DOODLE_TYPE;}
        void breed();
        void move();
        bool starve();
};

#endif