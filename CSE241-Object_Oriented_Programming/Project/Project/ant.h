#ifndef ANT_H
#define ANT_H

#include <iostream>
#include "organism.h"
#include "world.h"

class Ant : public Organism {
    friend class World;
    private:
        bool is_poison;
    public:
        Ant();
        Ant(World* earth, int x, int y);
        int getType();
        int isPoison() {return is_poison;}
        void setPoison() {is_poison=true;}
        void breed();
        void move();
        bool starve() {return false;}
};

#endif