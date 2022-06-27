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

int deleteVal(int value){
    NODE *prev;
    temp = head;
    for(int i = 1; temp->data != value; i++){
        prev = temp;
        temp = temp->next;
        if(temp == 0) break;
    }

    if(temp == 0){
        cout << "The value [" << value << "] doesn\'t exist in the list!" << endl;
        return false;
    } else {
        if(head->data == value){
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        if(temp == tail){
            tail = prev;
        } else {
            temp->next->prev = (temp->next == head) ? 0 : prev;
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
    add(60);
    add(70);

    deleteVal(10);
    deleteVal(40);
    deleteVal(70);
    print(head);
}