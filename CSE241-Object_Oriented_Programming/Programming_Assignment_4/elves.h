#ifndef __CREATURE__
#define __CREATURE__
#include "creature.h"
#endif

using namespace std;

class Elf : public Creature {
    public:
        Elf(){
            strength=10;
            health=10;
        }
        Elf(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        int getDamage() {
            // Magical attack %10 chance
            if(rand()%100 < 10)
                return 2 * Creature::getDamage();
            else // Normal attack
                return Creature::getDamage();
        }
        string getSpecies() {return "Elf";}
};