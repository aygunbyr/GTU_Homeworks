#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "ant.h"
#include "doodlebug.h"
using namespace std;

World::World() {
    int i, j, count_ant=0, count_doodle=0, x, y;
    // Make world clear
    for(i=0; i<WORLD_SIZE; i++)
        for(j=0; j<WORLD_SIZE; j++)
            earth[i][j]=NULL;
    
    // Create ants
    while(WORLD_ANTS > count_ant) {
        x = rand() % WORLD_SIZE;
        y = rand() % WORLD_SIZE;
        if(earth[x][y]==NULL) {
            Ant* new_ant = new Ant(this, x, y);
            count_ant++;
        }
    }

    // Create doodlebugs
    while(WORLD_DOODLES > count_doodle) {
        x = rand() % WORLD_SIZE;
        y = rand() % WORLD_SIZE;
        if(earth[x][y]==NULL) {
            Doodlebug* new_doodle = new Doodlebug(this, x, y);
            count_doodle++;
        }
    }
}

World::~World() {
    int i, j;
    for(i=0; i<WORLD_SIZE; i++)
        for(j=0; j<WORLD_SIZE; j++)
            if(earth[i][j]!=NULL)
                delete earth[i][j];
}


void World::setCell(Organism* o, int x, int y) {
    if(x < 0 || y < 0 || x >= WORLD_SIZE || y >= WORLD_SIZE)
        return;
    earth[x][y] = o;
}

Organism* World::getCell(int x, int y) {
    if(x < 0 || y < 0 || x >= WORLD_SIZE || y >= WORLD_SIZE)
        return NULL;
    return earth[x][y];
}

void World::printWorld() {
    int i, j;
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++) {
            if(earth[i][j]==NULL)
                cout << ".";
            else if(earth[i][j]->getType()==ANT_TYPE)
                cout << "o";
            else if(earth[i][j]->getType()==POISON_ANT_TYPE)
                cout << "c";            
            else if(earth[i][j]->getType()==DOODLE_TYPE)
                cout << "X";
        }
        cout << "\n";
    }
    cout << "\n";
}

void World::tick()
{
    int i,j;
    // Make sure any bug is not moved yet
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++)
        {
            if(earth[i][j] != NULL)
            {
                earth[i][j]->is_moved = false;
            }
        }
    }

    // Doodlebugs moves at first
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++)
        {
            if (earth[i][j]!=NULL && earth[i][j]->getType()==DOODLE_TYPE)
            {
                if(earth[i][j]->is_moved==false)
                {
                    earth[i][j]->is_moved = true;
                    earth[i][j]->move();
                }

            }
        }
    }

    // Ants move
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++)
        {
            if (earth[i][j]!=NULL && earth[i][j]->getType()==ANT_TYPE)
            {
                if(earth[i][j]->is_moved==false)
                {
                    earth[i][j]->is_moved = true;
                    earth[i][j]->move();
                }

            }
        }
    }

    // Some starving doodlebugs will die
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++)
        {
            if (earth[i][j]!=NULL && earth[i][j]->getType()==DOODLE_TYPE)
            {
                if (earth[i][j]->starve()==true)
                {
                    delete (earth[i][j]);
                    earth[i][j] = NULL;
                }

            }
        }
    }


    // At the end bugs will breed
    for(i=0; i<WORLD_SIZE; i++) {
        for(j=0; j<WORLD_SIZE; j++)
        {
            if (earth[i][j]!=NULL && earth[i][j]->is_moved==true)
            {
                earth[i][j]->breed();
            }
        }
    }
}