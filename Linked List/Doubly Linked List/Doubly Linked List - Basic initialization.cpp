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
    head->data = 50;
    tail = head;
    
    // Add more nodes
    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 60;
    tail->prev = prevnode;

    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 70;
    tail->prev = prevnode;

    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 80;
    tail->prev = prevnode;

    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 90;
    tail->prev = prevnode;

    prevnode = tail;
    tail->next = new NODE;
    tail = tail->next;
    tail->data = 100;
    tail->prev = prevnode;

    tail->next = 0; // Set the last node pointer NULL/0

    temp = head;
    while(temp != 0){
        cout << temp->data;
        temp = temp->next;
        if(temp != 0 ) cout << " => ";
    }
    cout << endl;
}