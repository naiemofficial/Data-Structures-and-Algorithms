#include <iostream>
using namespace std;

const int n = 5;
int A[n] = {0}, front = -1, rear = front;

int full(){
    return ((rear+1)%n == front);
}

int empty(){
    return (front == -1);
}

void push(int data){
    if(full()){
        cout << "[QUEUE IS FULL]! Element [" << data << "] not pushed into queue." << endl;
    } else {
        rear = (front == -1) ? ++front : ++rear;
        if(rear >= n) rear = rear%n;
        A[rear] = data;
    }
}

void pop(){
    if(empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else if(front == rear){
        front = rear = -1;
    } else {
        front++;
        if(front >= n) front = front%n;
    }
}

void print(){
    if(front == -1){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!empty()){
            cout << A[front];
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

    push(35);
    push(40);

    print();
}