#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail, *temp;
void add(int value){
    if(head == NULL){
        head = new NODE;
        head->data = value;
        head->next = 0;
        tail = head;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->data = value;
        tail->next = 0;
    }
}

void reverse(){
    if(head == NULL){
        cout << "The list can\'t be reversed" << endl;
    } else {
        temp = head;
        NODE *prev = 0, *next;
        while(temp != 0){
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        tail = head;
        head =  prev;
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

    reverse();
    print(head);
}