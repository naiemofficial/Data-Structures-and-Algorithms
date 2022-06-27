#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *head, *tail, *temp;
void add(int value){
    if(head == NULL){
        head = tail = new NODE;
        head->data = value;
        head->next = tail;
    } else {
        tail->next = new NODE;
        tail = tail->next;
        tail->data = value;
        tail->next = head;
    }
}

void reverse(){
    if(head == NULL){
        cout << "The list can\'t be reversed" << endl;
    } else {
        temp = head;
        NODE *prev = 0, *next;
        do {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        } while(temp != head);
        tail = head;
        head =  prev;
        tail->next = head;
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

    reverse();
    print(head);
}