#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

int main(){
    NODE *head, *tail, *temp;
    head = new NODE;
    
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

    tail->next = 0; // Set the last node pointer NULL/0

    if(head == 0){
        cout << "[EMPTY LIST]" << endl;
    } else {
        temp = head;
        while(temp != 0){
            cout << temp->data;
            temp = temp->next;
            if(temp != 0 ) cout << " => ";
        }
        cout << endl;
    }
}