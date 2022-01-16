#ifndef __CREATURE__
#define __CREATURE__
#include "creature.h"
#endif

using namespace std;

class Human : public Creature {
    public:
        Human(){
            strength=10;
            health=10;
        }
        Human(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        string getSpecies() {return "Human";}
        int getDamage() {
            return Creature::getDamage();
        }
};