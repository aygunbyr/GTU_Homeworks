#include <iostream>
using namespace std;

int getProductID( int ids[], string names[],int numProducts, string target)
{
    bool productFound;
    try {
        productFound=false;
        for(int i=0; i<numProducts; i++){
            if(names[i] == target)
            {
                productFound=true;
                return ids[i];
            }
        }
        if(!productFound)
            throw 1;
    }
    catch(int x){
        cout << "Error: Product not found!" << endl;
    }
    return -1;
}

int main()
{
    int productIds[] = {4, 5, 8, 10, 13};
    string products[] = {"computer","flash drive","mouse","printer","camera"};
    cout << getProductID(productIds, products, 5, "mouse") << endl;
    cout << getProductID(productIds, products, 5, "camera") << endl;
    cout << getProductID(productIds, products, 5, "laptop") << endl;
    return 0;
}
