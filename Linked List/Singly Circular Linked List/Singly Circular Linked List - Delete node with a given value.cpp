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

int deleteVal(int value){
    NODE *prev;
    temp = head;
    for(int i = 1; temp->data != value; i++){
        prev = temp;
        temp = temp->next;
        if(temp == head){
            temp = 0;
            break;
        }
    }

    if(temp == 0){
        cout << "The value [" << value << "] doesn\'t exist in the list!" << endl;
        return false;
    } else {
        if(head->data == value){
            if(head == tail){
                head = tail = 0;
            } else {
                head = temp->next;
                tail->next = head;
            }
        } else {
            prev->next = temp->next;
            if(temp == tail) tail = prev;
        }
        delete temp;
        return true;
    }
}

bool print(NODE *ref){
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

    deleteVal(10);
    deleteVal(40);
    deleteVal(70);
    print(head);
}