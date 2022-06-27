#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

int main(){
    NODE *head, *tail, *temp;    
    // Add first node
    head = new NODE;
    head->data = 10;
    head->next = 0;
    tail = head;

    // Add more nodes
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 20;

    tail->next = new NODE;
    tail = tail->next;
    tail->data = 30;

    tail->next = new NODE;
    tail = tail->next;
    tail->data = 40;

    tail->next = new NODE;
    tail = tail->next;
    tail->data = 50;

    tail->next = head; // Set the last node next pointer as head

    temp = head;
    do {
        cout << temp->data;
        temp = temp->next;
        if(temp != head) cout << " => ";
    } while(temp != head);
    cout << endl;
}