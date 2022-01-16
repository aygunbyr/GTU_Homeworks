#include <iostream>
#include <cstdlib>
#include <ctime>
#ifndef __CREATURE__
#define __CREATURE__
#include "creature.h"
#endif
#include "demons.h"
#include "elves.h"
#include "humans.h"
using namespace std;

int main() {
    // For random number generating
    srand((unsigned)time(0));

    Human human;
    Elf elf;
    Balrog balrog;
    Cyberdemon cyberdemon;

    Human custom_h(50,500);
    Elf custom_elf(30, 750);
    Balrog custom_b(40,900);
    Cyberdemon custom_cd(75,1250);

    cout << "Regular Creatures ###############" << endl;

    cout << human.getSpecies() << " has inflicted " << human.getDamage() << " damage!" << endl;
    cout << elf.getSpecies() << " has inflicted " << elf.getDamage() << " damage!" << endl;
    cout << balrog.getSpecies() << " has inflicted " << balrog.getDamage() << " damage!" << endl;
    cout << cyberdemon.getSpecies() << " has inflicted " << cyberdemon.getDamage() << " damage!" << endl;

    cout << "\nCustom Creatures ###############" << endl;

    cout << custom_h.getSpecies() << " has inflicted " << custom_h.getDamage() << " damage!" << endl;
    cout << custom_elf.getSpecies() << " has inflicted " << custom_elf.getDamage() << " damage!" << endl;
    cout << custom_b.getSpecies() << " has inflicted " << custom_b.getDamage() << " damage!" << endl;
    cout << custom_cd.getSpecies() << " has inflicted " << custom_cd.getDamage() << " damage!" << endl;

    return 0;
}