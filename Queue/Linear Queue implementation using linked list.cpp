#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *front, *rear;

int empty(){
    return (!front || !rear);
}

void push(int value){
    rear = (empty()) ? front = new NODE : rear->next = new NODE;
    rear->data = value;
    rear->next = 0;
}

void pop(){
    if(empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        NODE *temp = front;
        front = (front == rear) ? rear = 0 : front->next;
        delete temp;
    }
}

void print(){
    if(empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!empty()){
            cout << front->data;
            pop();
            if(!empty()) cout << " <= ";
        }
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