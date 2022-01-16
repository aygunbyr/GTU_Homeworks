#include <iostream>
#include <string>
using namespace std;

struct stringNode {
    char data;
    stringNode* prev;
    stringNode* next;
};

int main() {
    string str;
    int i;
    char temp_ch;
    stringNode* current;
    stringNode* head;
    stringNode* tail;
    stringNode* temp;
    stringNode* currentHead;
    stringNode* currentTail;
    cout << "Enter the string: ";
    getline(cin >> ws, str);

    head = new stringNode;

    current = head;

    for(i=0; i<str.length(); i++)
    {
        // update previous node
        if(current == head)
            current->prev = NULL;
        else
            current->prev = temp;

        // update data
        current->data = str[i];

        // update next node
        if(i<str.length()-1)
            current->next = new stringNode;
        else
        {
            current->next = NULL;
            tail = current;
        }

        // back up this then go next
        temp = current;
        current = current->next;
    }


    // backup head and tail
    currentHead = head;
    currentTail = tail;
    for(i=0; i<str.length()/2; i++)
    {
        // swap
        temp_ch = currentHead->data;
        currentHead->data = currentTail->data;
        currentTail->data = temp_ch;

        // traverse
        currentHead = currentHead->next;
        currentTail = currentTail->prev;
    }

    for(current=head; current != NULL; current=current->next)
        cout << current->data;


}
