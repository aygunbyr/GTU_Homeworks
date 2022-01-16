#include <iostream>
using namespace std;

class Polynomial {
    public:
    void get_polynomial_from_user();
    void print_polynomial();
    void setDegree(int d){*degree=d;}
    void setConstant(int c){*constant=c;}
    int getDegree(){return *degree;}
    double getConstant(){return *constant;}
    double getCoefficient(int index){return coefficients[index];}
    void setCoefficient(int index, double coef){coefficients[index] = coef;}
    Polynomial operator+(Polynomial p2);
    Polynomial operator-(Polynomial p2);
    // Default constructor
    Polynomial()
    {
        degree = new int;
        constant = new double;
    }
    // Constructor 2
    Polynomial(int deg){
        degree = new int;
        *degree = deg;
        constant = new double;
        *constant = 0.0;
        coefficients = new double[deg];
    }
    // Copy constructor
    Polynomial(Polynomial& Polynomial_old) 
    {
        int i;
        degree = new int;
        *degree = Polynomial_old.getDegree();
        constant = new double;
        *constant = Polynomial_old.getConstant();
        coefficients = new double[*degree];
        for(i=0; i<*degree; i++)
            coefficients[i] = Polynomial_old.getCoefficient(i);
    }

    private:
    int* degree;
    double* constant;
    double* coefficients;
};

int main() {
    Polynomial p1, p2, new_p;
    cout << "Polynomial #1" << endl;
    p1.get_polynomial_from_user();
    p1.print_polynomial();
    cout << "Polynomial #2" << endl;
    p2.get_polynomial_from_user();
    p2.print_polynomial();
    cout << "Sum of two polynomials:" << endl;
    new_p = p1+p2;
    new_p.print_polynomial();
    cout << "Subtraction of two polynomials:" << endl;
    new_p = p1-p2;
    new_p.print_polynomial();

    return 0;
}

void Polynomial :: get_polynomial_from_user() {
    int i;
    cout << "Enter degree for polynomial:";
    cin >> *degree;
    coefficients = new double[*degree];
    for(i=*degree; i>=1; i--)
    {
        cout << "Enter a coefficient for monomial x^" << i << " :";
        cin >> coefficients[i-1];
    }
    cout << "Enter constant number for polynomial: ";
    cin >> *constant;
}

void Polynomial :: print_polynomial() {
    int i;
    for(i=*degree; i>=1; i--)
    {
        if(coefficients[i-1] != 0)
        {
            if(coefficients[i-1]>0 && i!=*degree)
                cout << "+";
            cout.precision(3);
            cout << coefficients[i-1] << "x^" << i ;
        }
    }
    if(*constant>0)
        cout << "+";
    cout.precision(3);
    cout << *constant << endl;
}


Polynomial Polynomial :: operator+(Polynomial p2) {
    int i, new_polynomial_degree, which_is_bigger;
    if(*degree > p2.getDegree())
    {
        new_polynomial_degree = *degree;
        which_is_bigger=1;
    }   
    else if(p2.getDegree() > *degree)
    {
        new_polynomial_degree = p2.getDegree();
        which_is_bigger=2;
    } else if(p2.getDegree() == *degree)
    {
        new_polynomial_degree = *degree;
        which_is_bigger = 0;
    }

    // Create a temp polynomial to return then

    Polynomial temp(new_polynomial_degree);
    temp.setConstant( (*constant) + p2.getConstant() );

    if(which_is_bigger == 1)
    {
        for(i=0;i<p2.getDegree(); i++)
            temp.setCoefficient(i, coefficients[i] + p2.getCoefficient(i));
        for( ; i<*degree; i++)
            temp.setCoefficient(i, coefficients[i]);
    }
    else 
    if(which_is_bigger == 2)
    {
        for(i=0;i<*degree; i++)
            temp.setCoefficient(i, coefficients[i] + p2.getCoefficient(i));
        for( ; i<p2.getDegree(); i++)
            temp.setCoefficient(i, p2.getCoefficient(i));
    }
    else
    if(which_is_bigger == 0)
        for(i=0; i<new_polynomial_degree; i++)
            temp.setCoefficient(i, coefficients[i] + p2.getCoefficient(i));

    return temp;
}

Polynomial Polynomial :: operator-(Polynomial p2) {
    int i, new_polynomial_degree, which_is_bigger;
    if(*degree > p2.getDegree())
    {
        new_polynomial_degree = *degree;
        which_is_bigger=1;
    }   
    else if(p2.getDegree() > *degree)
    {
        new_polynomial_degree = p2.getDegree();
        which_is_bigger=2;
    } else if(p2.getDegree() == *degree)
    {
        new_polynomial_degree = *degree;
        which_is_bigger = 0;
    }

    // Create a temp polynomial to return then

    Polynomial temp(new_polynomial_degree);
    temp.setConstant( (*constant) + p2.getConstant() );

    if(which_is_bigger == 1)
    {
        for(i=0;i<p2.getDegree(); i++)
            temp.setCoefficient(i, coefficients[i] - p2.getCoefficient(i));
        for( ; i<*degree; i++)
            temp.setCoefficient(i, coefficients[i]);
    }
    else 
    if(which_is_bigger == 2)
    {
        for(i=0;i<*degree; i++)
            temp.setCoefficient(i, coefficients[i] - p2.getCoefficient(i));
        for( ; i<p2.getDegree(); i++)
            temp.setCoefficient(i, p2.getCoefficient(i));
    }
    else
    if(which_is_bigger == 0)
        for(i=0; i<new_polynomial_degree; i++)
            temp.setCoefficient(i, coefficients[i] - p2.getCoefficient(i));

    return temp;
}
