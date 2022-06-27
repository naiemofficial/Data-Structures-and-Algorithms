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

int deleteAt(int position){
    bool status = true;
    NODE *prev;
    temp = head;

    for(int i = 1; i < position; i++){
        prev = temp;
        temp = temp->next;
        if(temp == head){
            temp = 0;
            break;
        }
    }
    
    if(temp == 0 || position <= 0){
        cout << "The position [" << position << "] is invalid!" << endl;
        return false;
    } else {
        if(temp == head){
            if((head == tail)){
                head = tail = 0;
            } else {
                head = temp->next;
                tail->next = head;
                head->prev = tail;
            }
        } else {
            prev->next = temp->next;
            if(temp == tail){
                tail = prev;
                head->prev = tail;
            } else {
                temp->next->prev = prev;
            }
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
    add(60);
    add(70);

    deleteAt(1);
    deleteAt(3);
    deleteAt(5);
    print(head);
}