using namespace std;

class Creature
{
    public:
        Creature(){
            strength=10;
            health=10;
        }
        Creature(int newStrength, int newHit) {
            strength=newStrength;
            health=newHit;
        }
        int getDamage() {return (rand()%strength)+1;}
        int getHitpoints() {return health;}
        int getStrength() {return strength;}
        std::string getSpecies() {return "Unknown";}
        void setHitpoints(int newHealth) {health=newHealth;}
        void setStrength(int newStrength) {strength=newStrength;}

    protected:
        int strength; //a member data which stores the strength
        int health; //a member data which stores the hitpoints
};