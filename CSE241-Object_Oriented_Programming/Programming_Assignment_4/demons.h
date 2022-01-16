#ifndef __CREATURE__
#define __CREATURE__
#include "creature.h"
#endif

using namespace std;

class Demon : public Creature {
    public:
        Demon(){
            strength=10;
            health=10;
        }
        Demon(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        int getDamage() {
            // Demonic attack %5 chance
            if(rand()%100 < 5)
                return 50 + Creature::getDamage();
            else // Normal attack
                return Creature::getDamage();
        }
        string getSpecies() {return "Demon";}
};

class Balrog : public Demon {
    public:
        Balrog(){
            strength=10;
            health=10;
        }
        Balrog(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        int getDamage() {
            // Balrogs are very fast, so they get to attack twice
            return 2 * Demon::getDamage();
        }
        string getSpecies() {return "Balrog";}
};

class Cyberdemon : public Demon {
    public:
        Cyberdemon(){
            strength=10;
            health=10;
        }
        Cyberdemon(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        int getDamage() {
            return Demon::getDamage();
        }
        string getSpecies() {return "Cyberdemon";}
};