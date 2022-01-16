#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 16

struct person
{
    char name[STRING_LEN];
    char surname[STRING_LEN];
    char musical_work[STRING_LEN];
    int age;
    struct person *next;
};
struct person *top;

void addNode(char name[], char surname [], char creation [], int age)
{
    // create a temp person
    struct person *temp;
    temp = (struct person*) malloc(sizeof(struct person));

    // assign strings
    strcpy(temp->name, name);
    strcpy(temp->surname, surname);
    strcpy(temp->musical_work, creation);
    temp->age = age;

    // temp's next is top
    temp->next = top;

    // new top is temp
    top = temp;
}

void deleteNode() 
{
    struct person *current;
    if(top == NULL)
        printf("Stack is empty!\n");
    else
    {
        // get top to delete later
        current = top;
        
        // new top is top's next
        top = top->next;

        // free memory        
        free(current);
    }
}

void sort_Alphabetically() 
{
    struct person *current, *temp, temp_per;
    int c=0, i, j;

    for(current = top; current != NULL; current = current->next) c++;

    current = top;

    for(i=0; i < c-1; i++, current = current->next)
    {
        temp = current->next;
        for(j=i+1; j < c; j++, temp = temp->next)
        {
            if(strcmp(current->name, temp->name) > 0)
            {
                // swap
                strcpy(temp_per.name, current->name);
                strcpy(current->name, temp->name);
                strcpy(temp->name, temp_per.name);

                strcpy(temp_per.surname, current->surname);
                strcpy(current->surname, temp->surname);
                strcpy(temp->surname, temp_per.surname);

                strcpy(temp_per.musical_work, current->musical_work);
                strcpy(current->musical_work, temp->musical_work);
                strcpy(temp->musical_work, temp_per.musical_work);

                temp_per.age = current->age;
                current->age = temp->age;
                temp->age = temp_per.age;
            }
        }
    }
}

void sort_Increasingly() 
{
    struct person *current, *temp, temp_per;
    int c=0, i, j;

    for(current = top; current != NULL; current = current->next) c++;

    current = top;

    for(i=0; i < c-1; i++, current = current->next)
    {
        temp = current->next;
        for(j=i+1; j < c; j++, temp = temp->next)
        {
            if(current->age > temp->age)
            {
                // swap
                strcpy(temp_per.name, current->name);
                strcpy(current->name, temp->name);
                strcpy(temp->name, temp_per.name);

                strcpy(temp_per.surname, current->surname);
                strcpy(current->surname, temp->surname);
                strcpy(temp->surname, temp_per.surname);

                strcpy(temp_per.musical_work, current->musical_work);
                strcpy(current->musical_work, temp->musical_work);
                strcpy(temp->musical_work, temp_per.musical_work);

                temp_per.age = current->age;
                current->age = temp->age;
                temp->age = temp_per.age;
            }
        }
    }
}

void print_stack()
{
    int i=1;
    struct person *current;
    current = top;
    while(current != NULL)
    {
        printf("%d-)\n%s\n%s\n%s\n%d\n", i, current->name, current->surname, current->musical_work, current->age);
        current = current->next;
        i++;
    }
}

int main(void) 
{
    int choice=0, age;
    char name[STRING_LEN], surname[STRING_LEN], creation[STRING_LEN];
    top = NULL;

    // menu
    while(choice != 5)
    {
        printf("****MENU****\n  1-  Add a person to the stack\n  2-  Pop a person from the stack\n  3-  Sort in alphabetical order\n  4-  Sort by ages in ascending order\n  5-  Exit menu\n************\nSelect your option: ");
        scanf("%d", & choice);

        switch( choice )
        {
            case 1:
                // add person then print
                printf("Name: ");
                scanf(" %40[^\n]s", name);

                printf("Surname: ");
                scanf(" %40[^\n]s", surname);

                printf("Creation: ");
                scanf(" %40[^\n]s", creation);

                printf("Age: ");
                scanf("%d", &age);

                addNode(name, surname, creation, age);
                print_stack();
                break;

            case 2:
                // delete person then print
                deleteNode();
                print_stack();
                break;

            case 3:
                // sort by name alphabetically then print
                sort_Alphabetically();
                print_stack();
                break;

            case 4:
                // sort by age then print
                sort_Increasingly();
                print_stack();
                break;

            default:
                break;
        }

    }
    return 0;
}