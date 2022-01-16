#include <iostream>
using namespace std;

class Person {
    public:
        Person(){name="";}
        Person(string theName){name=theName;}
        Person(const Person& theObject){name=theObject.name;}
        string getName() const {return name;}
        Person& operator=(const Person& rtSide){
            name=rtSide.getName(); 
            return *this;
        }
        friend istream& operator>>(istream& inStream, Person& personObject);
        friend ostream& operator<<(ostream& outStream, const Person& personObject);

    private:
        string name;
};

class Vehicle {
    public:
        Vehicle();
        Vehicle(string manufacturer){manufacturer_name=manufacturer;}
        Vehicle(string manufacturer, int cc, Person own){
            manufacturer_name=manufacturer;
            engine_cylinder_count=cc;
            owner = own;
        }
        string getManName() {return manufacturer_name;}
        int getCylinderCount() {return engine_cylinder_count;}
        Person getOwner() {return owner;}
        void setManName(string man_name) {manufacturer_name=man_name;}
        void setCylinderCount(int count){engine_cylinder_count=count;}
        void setOwner(Person ps){owner=ps;}
        void operator=(Vehicle vh){
            manufacturer_name=vh.getManName();
            engine_cylinder_count=vh.getCylinderCount();
            owner=vh.getOwner();
        }
        Vehicle(const Vehicle& theObject){
            manufacturer_name = theObject.manufacturer_name;
            engine_cylinder_count=theObject.engine_cylinder_count;
            owner=theObject.owner;
        }
    protected:
        string manufacturer_name;
        int engine_cylinder_count;
        Person owner;
};


class Truck : public Vehicle {
    public:
        double getLoadCapacity(){return load_capacity_tons;}
        double getTowingCapacity(){return towing_capacity;}
        void setLoadCapacity(double loadc){load_capacity_tons=loadc;}
        void setTowingCapacity(double towc){towing_capacity=towc;}

        void operator=(Truck tr){
            manufacturer_name=tr.getManName();
            engine_cylinder_count=tr.getCylinderCount();
            owner=tr.getOwner();
            load_capacity_tons=tr.getLoadCapacity();
            towing_capacity=tr.getTowingCapacity();
        }
        Truck(const Truck& theObject){
            manufacturer_name = theObject.manufacturer_name;
            engine_cylinder_count=theObject.engine_cylinder_count;
            owner=theObject.owner;
            load_capacity_tons=theObject.load_capacity_tons;
            towing_capacity=theObject.towing_capacity;
        }

    private:
        double load_capacity_tons;
        double towing_capacity;
};


int main() {
    Person a("Ahmet"), b("Baris");
    
    Vehicle va("Volvo", 144, a);
    Vehicle vb("Scania", 112, b);
    cout << "VEHICLE A" << endl;
    cout << "Manufacturer: " << va.getManName() << endl;
    cout << "Cylinder count: " << va.getCylinderCount() << endl;
    cout << "Owner's name: " << va.getOwner().getName() << endl;
    cout << "VEHICLE B" << endl;
    cout << "Manufacturer: " << vb.getManName() << endl;
    cout << "Cylinder count: " << vb.getCylinderCount() << endl;
    cout << "Owner's name: " << vb.getOwner().getName() << endl;

    va=vb;

    cout << "Vehicle B is assigned to Vehicle A." << endl;

    cout << "VEHICLE A" << endl;
    cout << "Manufacturer: " << va.getManName() << endl;
    cout << "Cylinder count: " << va.getCylinderCount() << endl;
    


    return 0;
}

