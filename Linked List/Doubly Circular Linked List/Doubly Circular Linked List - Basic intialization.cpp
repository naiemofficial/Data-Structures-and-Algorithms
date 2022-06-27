#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *prev;
    NODE *next;
};

int main(){
    NODE *head, *tail, *prevnode, *temp;    
    // Add first node
    head = new NODE;
    head->data = 10;
    head->next = 0;
    tail = head;

    // Add more nodes
    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 20;
    tail->prev = prevnode;

    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 30;
    tail->prev = prevnode;
    
    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 40;
    tail->prev = prevnode;
    
    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 50;
    tail->prev = prevnode;

    tail->next = head; // Set the last node next pointer as head
    head->prev = tail; // Set the head node previous pointer as the tail

    temp = head;
    do {
        cout << temp->data;
        temp = temp->next;
        if(temp != head) cout << " => ";
    } while(temp != head);
}