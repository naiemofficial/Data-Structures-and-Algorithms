#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *front, *rear;

int empty(){
    return (front == 0);
}

void push(int value){
    if(empty()){
        rear = front = new NODE;
    } else {
        rear = rear->next = new NODE;
    }
    rear->data = value;
    rear->next = front;
}

void pop(){
    if(empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        NODE *temp = front;
        front = (front == rear) ? rear = 0 : front->next;
        if(rear) rear->next = front;
        delete temp;
    }
}

void print(){
    NODE *temp = front;
    if(temp == 0){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        do {
            cout << front->data;
            pop();
            if(!empty()) cout << " <= ";
        } while(!empty());
        cout << endl;
    }
}

int main(){
    push(5);
    push(10);
    push(15);
    push(20);
    push(25);

    pop();
    pop();

    print();
}