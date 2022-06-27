#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *prev;
    NODE *next;
};

NODE *head, *tail, *prevnode, *temp;
void add(int value){
    if(head == NULL){
        head = tail = new NODE;
        head->data = value;
        head->prev = head->next = tail;
    } else {
        prevnode = tail;
        tail->next = head->prev = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
        tail->data = value;
        tail->next = head;
    }
}

int deleteBegin(){
    temp = head;
    if(temp == 0){
        cout << "Action not complete" << endl;
        return false;
    } else {
        if(temp->next == head){
            head = tail = 0;
        } else {
            head = temp->next;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
        return true;
    }
}

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        do {
            cout << ref->data;
            ref = ref->next;
            if(ref != head) cout << " => ";
        } while(ref != head);
        cout << endl;
        return true;
    }
}

int main(){
    add(10);
    add(20);
    add(30);
    add(40);
    add(50);
    
    deleteBegin();
    deleteBegin();
    print(head);
}