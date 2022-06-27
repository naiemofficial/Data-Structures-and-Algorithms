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

void addTo(int position, int value){
    temp = head;
    if(position >= 1){    
        for(int i = 1; i < position-1; i++){
            temp = temp->next; // point to position immediate previous node
            if(temp == 0) break;
        }
        if(temp || position == 1){
            NODE *newnode = new NODE;
            newnode->data = value;
            if(position == 1){
                newnode->next = head;
                head = temp = newnode;
                if(head->next == 0) tail = head;
            } else {
                newnode->next = temp->next;
                temp->next = newnode;
                if(newnode->next == 0) tail = newnode;
            }
        }
    }
    if(position < 1 || temp == 0){
        cout << "Data not inserted. Invalid position [" << position <<"]." << endl;
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
    addTo(1, 5);
    addTo(3, 15);
    addTo(6, 35);
    print(head);
}