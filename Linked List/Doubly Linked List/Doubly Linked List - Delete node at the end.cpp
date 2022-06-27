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
        head = new NODE;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        prevnode = tail;
        tail->next = new NODE;
        tail = tail->next;
        tail->prev = prevnode;
        tail->data = value;
        tail->next = 0;
    }
}

int deleteEnd(){
    NODE *prev;
    temp = head;

    if(temp == 0){
        cout << "Action not complete" << endl;
        return false;
    } else {
        while(temp->next != 0){
            prev = temp;
            temp = temp->next;
        }

        if(prev->next == 0){
            head = 0;
        } else {
            prev->next = 0;
        }
        if(temp->next == 0) tail = prev;
        delete temp;
        return true;
    }
}

int print(NODE *ref){
    if(ref == 0){
        cout << "[EMPTY LIST]" << endl;
        return false;
    } else {
        while(ref != 0){
            cout << ref->data;
            ref = ref->next;
            if(ref != 0 ) cout << " => ";
        }
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

    deleteEnd();
    deleteEnd();
    print(head);
}