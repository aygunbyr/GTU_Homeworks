#include <iostream>
using namespace std;

class Pizza {
    public:
    int getType(){return type;}
    int getSize(){return size;}
    int getToppings(){return toppings;}
    double getPrice(){return price;}
    void setType(int t){type=t;}
    void setSize(int s){size=s;}
    void setToppings(int c){toppings=c;}
    void setPrice(double pr){price=pr;}
    double computePrice(const int type, const int size, const int toppings);
    void outputDescription();

    private:
    int type, size, toppings;
    double price;
};

double Pizza::computePrice(const int type, const int size, const int toppings) {
    double price=0.0;
    switch(size) {
        // Small size
        case 1:
            price += 10.00;
            break;

        // Medium size
        case 2:
            price += 14.00;
            break;

        // Big size
        case 3:
            price += 17.00;
            break;

        default:
            break;
    }
    price += 2.0 * toppings;
    return price;
}

void Pizza::outputDescription() {
    cout << "Pizza Type: ";
    switch(type) {
        case 1:
            cout << "Deep Dish";
            break;

        case 2:
            cout << "Hand Tossed";
            break;

        case 3:
            cout << "Pan";
            break;

        default:
            break;
    }
    cout << endl;
    cout << "Size: ";
    switch(size) {
        case 1:
            cout << "Small";
            break;
        
        case 2:
            cout << "Medium";
            break;

        case 3:
            cout << "Big";
            break;

        default:
            break;
    }
    cout << endl;
    cout << "Toppings count: " << toppings << endl;
    cout << "Price: " << fixed << price << endl;
}


int main() {
    int input;
    double pr;
    Pizza pizza1;

    // Get pizza date from user
    cout << "Enter pizza type (Deep dish = 1, Handtossed = 2, Pan = 3): ";
    cin >> input;
    pizza1.setType(input);
    cout << "Enter pizza size (Small = 1, Medium = 2, Big = 3): ";
    cin >> input;
    pizza1.setSize(input);
    cout << "Enter number of toppings on Pizza: ";
    cin >> input;
    pizza1.setToppings(input);

    // Compute price of pizza
    pr=pizza1.computePrice(pizza1.getType(), pizza1.getSize(), pizza1.getToppings());
    pizza1.setPrice(pr);

    // Print pizza output
    pizza1.outputDescription();
    
    return 0;
}