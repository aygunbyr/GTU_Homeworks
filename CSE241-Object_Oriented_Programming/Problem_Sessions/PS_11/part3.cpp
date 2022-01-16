#include <iostream>
using namespace std;

struct node {
    struct node* next;
    int value;
};

void initialize(struct node* head);
void print(struct node* head);
void reverse(struct node*& head);

int main() {
    struct node* list;
    list = new struct node;
    initialize(list);

    // Print in normal case
    cout << "Normal ordered list:" << endl;
    print(list);

    // Reverse then print again
    cout << "Reverse ordered list:" << endl;
    reverse(list);
    print(list);

    return 0;
}

void initialize(struct node* head) {
    struct node* current;
    int i;
    i=1;

    // simply initialize a linked list
    for(current=head; i<=5 ;current=current->next)
    {
        current->value = i*5;
        if(i!=5)
            current->next = new struct node;
        else
            current->next = NULL;
        i++;
    }
}

void print(struct node* head) {
    struct node* current;

    for(current=head; current!=NULL; current=current->next)
        cout << current->value << endl;
}

void reverse(struct node*& head) {
    struct node* reverse;
    struct node* temp;
    struct node* current;

    // reverse
    for(current=head; current!=NULL; current=current->next)
    {
            temp = new struct node;
            temp->value = current->value;
            if(current==head)
                temp->next = NULL;
            else
                temp->next = reverse;
            reverse = temp;
    }

    // assign reversed list to original list pointer
    head=reverse;
}
