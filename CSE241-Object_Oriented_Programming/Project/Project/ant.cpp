#include <iostream>
#include <cstdlib>
#include "ant.h"
#include "organism.h"
#include "world.h"
using namespace std;
// Ant class inherits from Bug class
Ant::Ant() : Organism() {is_poison=false;}
Ant::Ant(World* earth, int x, int y) : Organism(earth,x,y) {
    is_poison=false;
}

int Ant::getType() {
    if(is_poison==false)
        return ANT_TYPE;
    else
        return POISON_ANT_TYPE;
}

void Ant::breed() {
    breed_time++;
    if((breed_time == BREED_ANT && is_poison==false)||(breed_time == BREED_POISON_ANT && is_poison==true))
    {
        // Time to breed...
        breed_time = 0;
        if(x > 0 && worldPtr->getCell(x-1, y) == NULL )
        {
            if(is_poison==false)
            {
                Ant* new_ant = new Ant(worldPtr, x-1, y);
                // Mutation makes that baby poisonous
                if((rand() % 100) < MUTATION_PERCENT)
                    new_ant->setPoison();
            }
            else if(is_poison==true) {
                Ant* new_ant = new Ant(worldPtr, x-1, y);
                new_ant->setPoison();
            }
        } else if(x < WORLD_SIZE - 1 && worldPtr->getCell(x+1, y) == NULL )
        {
            if(is_poison==false)
            {
                Ant* new_ant = new Ant(worldPtr, x+1, y);
                // Mutation makes that baby poisonous
                if((rand() % 100) < MUTATION_PERCENT)
                    new_ant->setPoison();
            }
            else if(is_poison==true) {
                Ant* new_ant = new Ant(worldPtr, x+1, y);
                new_ant->setPoison();
            }
        } else if(y > 0 && worldPtr->getCell(x, y-1) == NULL )
        {
            if(is_poison==false)
            {
                Ant* new_ant = new Ant(worldPtr, x, y-1);
                // Mutation makes that baby poisonous
                if((rand() % 100) < MUTATION_PERCENT)
                    new_ant->setPoison();
            }
            else if(is_poison==true) {
                Ant* new_ant = new Ant(worldPtr, x, y-1);
                new_ant->setPoison();
            }
        } else if(y < WORLD_SIZE - 1 && worldPtr->getCell(x, y+1) == NULL )
        {
            if(is_poison==false)
            {
                Ant* new_ant = new Ant(worldPtr, x, y+1);
                // Mutation makes that baby poisonous
                if((rand() % 100) < MUTATION_PERCENT)
                    new_ant->setPoison();
            }
            else if(is_poison==true) {
                Ant* new_ant = new Ant(worldPtr, x, y+1);
                new_ant->setPoison();
            }
        }
    }
}

void Ant::move() {
    // Moves to a random direction
    int direction = rand() % 4;

    if(direction == 0) {
        if((y>0) && worldPtr->getCell(x, y-1) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x, y-1);
            worldPtr->setCell(NULL,x,y);
            y--;
        }
    }
    else if(direction == 1) {
        if((y < WORLD_SIZE - 1) && worldPtr->getCell(x, y+1) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x, y+1);
            worldPtr->setCell(NULL,x,y);
            y++;
        }
    }
    else if(direction == 2) {
        if((x>0) && worldPtr->getCell(x-1, y) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x-1, y);
            worldPtr->setCell(NULL,x,y);
            x--;
        }
    }
    else if(direction == 3) {
        if((x < WORLD_SIZE - 1) && worldPtr->getCell(x+1, y) == NULL) {
            worldPtr->setCell(worldPtr->getCell(x, y), x+1, y);
            worldPtr->setCell(NULL,x,y);
            x++;
        }
    }
}