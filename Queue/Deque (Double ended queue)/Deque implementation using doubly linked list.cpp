#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *prev;
    NODE *next;
};

NODE *front, *rear, *prevnode, *temp;

int empty(){
    return (!front);
}

void push_back(int value){
    prevnode = rear;
    rear = (front == NULL) ? front = new NODE : rear->next = new NODE;
    rear->prev = prevnode;
    rear->data = value;
    rear->next = 0;
}

void push_front(int value){
    temp = new NODE;
    temp->data = value;
    temp->next = front;
    if(front) front->prev = temp;
    front = temp;
    if(front->next == 0) rear = front;
    temp->prev = 0;
}

void pop_front(){
    temp = front;
    if(empty()){
        cout << "[DE-QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        front = temp->next;
        if(front){
            front->prev = 0;
        } else {
            rear = 0;
        }
        delete temp;
    }
}

void pop_back(){
    NODE *prev;
    temp = front;

    if(empty()){
        cout << "[DE-QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        while(temp->next != 0){
            prev = temp;
            temp = temp->next;
        }
        if(prev->next == 0){
            front = 0;
        } else {
            prev->next = 0;
        }
        if(temp->next == 0) rear = prev;
        delete temp;
    }
}

void print(){
    if(empty()){
        cout << "[EMPTY LIST]" << endl;
    } else {
        while(!empty()){
            cout << front->data;
            pop_front();
            if(!empty()) cout << " <= ";
        }
        cout << endl;
    }
}

int main(){
    push_front(15);
    push_front(10);
    push_front(5);
    push_back(20);
    push_back(25);

    pop_back();
    push_front(2);
    pop_front();
    pop_back();

    print();
}