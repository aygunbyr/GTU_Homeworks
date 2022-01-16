#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Organism {
    public:
        void move();
        char getType() {return type;}
        void setAsBlank(int cx, int cy) {
            x = cx;
            y = cy;
            move_count = 0;
            type=' ';
        }
        void operator=(const Organism& other){
            x = other.x;
            y = other.y;
            move_count = other.move_count;
            type = other.type;
        }
        
    protected:
        int x;
        int y;
        int move_count;
        char type;
};

class Ant : public Organism {
    public:
        void move(Organism world[][20]);
        void breed(Organism world[][20]);
        Ant();
        Ant(int cx, int cy) {
            x = cx;
            x = cy;
            move_count = 0;
            type = 'O';
        }
        
};

class Doodlebug : public Organism {
    public:
        void move(Organism world[][20]);
        Doodlebug();
        Doodlebug(int cx, int cy) {
            x = cx;
            y = cy;
            move_count = 0;
            type = 'X';
        }
};

void initialize_world(Organism world[][20]);
void print_world(Organism world[][20]);

int main() {
    srand(time(NULL));
    Organism world[20][20];
    initialize_world(world);
    cout << "######## WORLD ######## " << endl;
    print_world(world);
    

    return 0;
}


void initialize_world(Organism world[][20]) {
    int i, x, y;
    int ant_count = 100;

    // Fill whole world with blank
    for(x=0; x<20; x++)
        for(y=0; y<20; y++)
            world[x][y].setAsBlank(x, y);

    // Place five doodlebugs into the world
    for(i=0; i<5; i++)
    {
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while(world[x][y].getType() == 'X' || world[x][y].getType() == 'O');
        world[x][y] = Doodlebug(x,y);
    }

    // Place one hundred ants into the world
    for(i=0; i<100; i++)
    {
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while(world[x][y].getType() == 'X' || world[x][y].getType() == 'O');
        world[x][y] = Ant(x,y);
    }
}

void print_world(Organism world[][20]) {
    int i, j;
    for(i=0; i<20; i++)
    {
        for(j=0; j<20; j++)
            cout << "[" << world[i][j].getType() << "]";
        cout << endl;
    }
}
