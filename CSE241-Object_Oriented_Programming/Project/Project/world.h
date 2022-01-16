#ifndef WORLD_H
#define WORLD_H
#include "organism.h"

// Global constants that set simulation
const int WORLD_SIZE=20;
const int WORLD_ANTS=100;
const int WORLD_DOODLES=5;
const int ANT_TYPE=1;
const int DOODLE_TYPE=2;
const int POISON_ANT_TYPE=11;
const int BREED_ANT=3;
const int BREED_DOODLE=8;
const int BREED_POISON_ANT=4;
const int STARVE_TIME_DOODLE=3;
const int MOVE_AFTER_POISON=2;
const int MUTATION_PERCENT=5;

class World {
    friend class Organism;
    friend class Ant;
    friend class Doodlebug;
    private:
        Organism* earth[WORLD_SIZE][WORLD_SIZE];

    public:
        World();
        virtual ~World();
        void setCell(Organism* o, int x, int y);
        Organism* getCell(int x, int y);
        void printWorld();
        void tick();
};

#endif