#include <iostream>
#include "doodlebug.h"
#include "organism.h"
using namespace std;

// Doodlebug class inherits from Bug class
Doodlebug::Doodlebug() : Organism() {
    starve_time=0;
    poison_eaten=false;
    moves_after_poison=0;
}
Doodlebug::Doodlebug(World* earth, int x, int y) : Organism(earth,x,y) {
    starve_time=0;
    poison_eaten=false;
    moves_after_poison=0;
}

void Doodlebug::breed() {
    breed_time++;
    if(breed_time == BREED_DOODLE)
    {
        // Time to breed...
        breed_time = 0;
        if(x > 0 && worldPtr->getCell(x-1, y) == NULL )
            Doodlebug* new_doodle = new Doodlebug(worldPtr, x-1, y);
        else if(x < WORLD_SIZE - 1 && worldPtr->getCell(x+1, y) == NULL )
            Doodlebug* new_doodle = new Doodlebug(worldPtr, x+1, y);
        else if(y > 0 && worldPtr->getCell(x, y-1) == NULL )
            Doodlebug* new_doodle = new Doodlebug(worldPtr, x, y-1);
        else if(y < WORLD_SIZE - 1 && worldPtr->getCell(x, y+1) == NULL )
            Doodlebug* new_doodle = new Doodlebug(worldPtr, x, y+1);
    }
}

void Doodlebug::move()
{
    // Update time for poisoned ones
    if(poison_eaten==true)
        moves_after_poison++;

    // Poisoned doodlebugs will die
    if(poison_eaten==true && moves_after_poison >= MOVE_AFTER_POISON)
    {
        delete (worldPtr->earth[x][y]);
        return;
    }

    // If it finds an ant then will eat otherwise moves randomly

    // Lets look around for some food
    if(y>0 && worldPtr->getCell(x, y-1)!=NULL && worldPtr->getCell(x, y-1)->getType() == ANT_TYPE)
    {
        delete(worldPtr->earth[x][y-1]);
        worldPtr->earth[x][y-1] = this;
        worldPtr->setCell(NULL, x, y);
        starve_time = 0; // Starving has reset
        y--;
        return; // Move is done
    } else if(y < WORLD_SIZE - 1 && worldPtr->getCell(x, y+1)!=NULL && worldPtr->getCell(x, y+1)->getType() == ANT_TYPE)
    {
        delete(worldPtr->earth[x][y+1]);
        worldPtr->earth[x][y+1] = this;
        worldPtr->setCell(NULL, x, y);
        starve_time = 0; // Starving has reset
        y++;
        return; // Move is done
    } else if(x>0 && worldPtr->getCell(x-1, y)!=NULL && worldPtr->getCell(x-1, y)->getType() == ANT_TYPE)
    {
        delete(worldPtr->earth[x-1][y]);
        worldPtr->earth[x-1][y] = this;
        worldPtr->setCell(NULL, x, y);
        starve_time = 0; // Starving has reset
        x--;
        return; // Move is done
    } else if(y>0 && worldPtr->getCell(x+1, y)!=NULL && worldPtr->getCell(x+1, y)->getType() == ANT_TYPE)
    {
        delete(worldPtr->earth[x+1][y]);
        worldPtr->earth[x+1][y] = this;
        worldPtr->setCell(NULL, x, y);
        starve_time = 0; // Starving has reset
        x++;
        return; // Move is done
    }

    // Move randomly
    int direction = rand() % 4;

    if(direction == 0) {
        if((y>0) && worldPtr->getCell(x, y-1) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x, y-1);
            worldPtr->setCell(NULL,x,y);
            y--;
            starve_time++;
        }
    }
    else if(direction == 1) {
        if((y < WORLD_SIZE - 1) && worldPtr->getCell(x, y+1) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x, y+1);
            worldPtr->setCell(NULL,x,y);
            y++;
            starve_time++;
        }
    }
    else if(direction == 2) {
        if((x>0) && worldPtr->getCell(x-1, y) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x-1, y);
            worldPtr->setCell(NULL,x,y);
            x--;
            starve_time++;
        }
    }
    else if(direction == 3) {
        if((x < WORLD_SIZE - 1) && worldPtr->getCell(x+1, y) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x+1, y);
            worldPtr->setCell(NULL,x,y);
            x++;
            starve_time++;
        }
    }
}

bool Doodlebug::starve() {
    if(starve_time >= STARVE_TIME_DOODLE)
        return true;
    return false;
}