#include "stdio.h" 
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define PI 3
#define Square 1
#define Rectangular 2
#define Circular 3
#define Red 0
#define Yellow 1
#define Blue 2
#define Black 3
#define White 4

double CreateBody(int shape) { // Tested approved
    double area, edge, edge2, radius;
    switch (shape) {
    case Square: // Area of square
        printf("Enter length of an edge:");
        scanf("%lf", &edge);
        area = edge * edge;
        break;

    case Rectangular: // Area of rectangular
        printf("Enter length of first edge:");
        scanf("%lf", &edge);
        printf("Enter length of second edge:");
        scanf("%lf", &edge2);
        area = edge * edge2;
        break;

    case Circular: // Area of circular
        printf("Enter radius of circle:");
        scanf("%lf", &radius);
        area = PI * radius * radius;
        break;

    default:
        break;
    }
    return area;
}

int SetColor(int color) {
    // Revise color
    if (color >= 0 && color <= 1000)
        return color % 5;
    else
        return 1;
}

double LoadMoves(int shape, double body_size) {
    double perimeter, long_edge, radius;
    // Calculate perimeter which is equals to length of move
    switch (shape) {
    case 1: // Perimeter of square
        perimeter = 4 * sqrt(body_size);
        break;

    case 2: // Perimeter of rectangular
        long_edge = body_size / 5;
        perimeter = (long_edge + 5) * 2;
        break;

    case 3: // Perimeter of circular
        radius = sqrt(body_size / PI);
        perimeter = 2 * PI * radius;
        break;

    default:
        break;
    }
    return perimeter;
}

int setAtackPower(int lower_bound, int upper_bound) {
    // Set attack power as random number
    int attack_power;
    srand(time(NULL));
    attack_power = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
    return attack_power;
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power) {
    int edge, i, j, k, radius;
    // Print shape and pokemon name
    switch (shape) {
    case Square:
        edge = sqrt(body_size);
        for (i = 0; i < edge; i++) {
            for (j = 0; j < edge; j++)
                printf("X");
            printf("\n");
        }
        printf("Name: Square Pokemon");
        break;

    case Rectangular:
        edge = body_size / 5;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < edge; j++)
                printf("X");
            printf("\n");
        }
        printf("Name: Rectangular Pokemon");
        break;

    case Circular:
        radius = sqrt(body_size / PI);
        // Print circle
        if (radius % 2 == 1 || radius % 2 == 0) {
            for (i = 0; i < radius; i++) { // radius kadar satır olacak, satırları basan for
                for (j = 0; j < abs(radius / 2 - i); j++)
                    // Print tabs before X
                    if (!(radius % 2 == 0 && j == abs(radius / 2 - i) - 1 && i == 0))
                        printf("\t\t");
                // If radius is even, print 1/2 tab (2 whitespaces)
                if (i == 0 && radius % 2 == 0)
                    printf("\t");
                printf("X");
                for (k = 0; k < ((radius / 2) - j) * 2; k++)
                    if (!(radius % 2 == 0 && k == ((radius / 2) - j) * 2 - 1))
                        printf("\t\t");
                if (i != 0 && ((radius % 2 == 1 && i != radius - 1) || radius % 2 == 0)) {
                    printf("X");
                }
                printf("\n");
            }
            if (radius % 2 == 0) {
                // If radius is even and it is last line
                for (i = 0; i < (radius / 2) - 1; i++)
                    printf("\t\t");
                printf("\tX");
                printf("\n");
            }
        }
        printf("Name: Circular Pokemon");
        break;

    default:
        break;
    }

    printf("\nSize: %.2lf", body_size);

    // Print color. We have 5 colors so we use mod five of color code
    printf("\nColor: ");
    switch (color) {
    case Red:
        printf("Red");
        break;

    case Yellow:
        printf("Yellow");
        break;

    case Blue:
        printf("Blue");
        break;

    case Black:
        printf("Black");
        break;

    case White:
        printf("White");
        break;

    default:
        break;
    }

    // Print move length and attack power
    printf("\nMove: %.2lf", move_length);
    printf("\nAttack Power: %d\n", attack_power);
}

int main() {
    int shape, color, attack_power;
    double size_of_body, move_length;
    shape = 3;
    size_of_body = CreateBody(shape);
    color = 798;
    color = SetColor(color);
    move_length = LoadMoves(shape, size_of_body);
    attack_power = setAtackPower(0, 150);
    ShowPokemon(shape, size_of_body, color, move_length, attack_power);
    return 0;
}