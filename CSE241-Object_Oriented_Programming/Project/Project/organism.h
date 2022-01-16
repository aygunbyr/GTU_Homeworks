#ifndef ORGANISM_H
#define ORGANISM_H

class World;

class Organism {
    friend class World;
    protected:
        int x, y;
        int breed_time;
        bool is_moved;
        World* worldPtr;

    public:
        Organism();
        Organism(World* earth, int x, int y);
        virtual ~Organism();
        virtual int getType() = 0;
        World* getWorldPtr() {return worldPtr;}
        virtual void breed() = 0;
        virtual void move() = 0;
        virtual bool starve() = 0;
};

#endif