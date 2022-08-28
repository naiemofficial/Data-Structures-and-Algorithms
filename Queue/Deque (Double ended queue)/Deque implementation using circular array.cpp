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

void push_front(int data){
    if(full()){
        cout << "[QUEUE IS FULL]! Element [" << data << "] not pushed into deque." << endl;
    } else {
        if(front == 0 && rear >= front){
            front = n-1;
        } else {
            front = (front == -1) ? rear = ++ front : --front;
        }
        A[front] = data;
    }
}

void push_back(int data){
    if(full()){
        cout << "[QUEUE IS FULL]! Element [" << data << "] not pushed into deque." << endl;
    } else {
        rear = (front == -1) ? ++front : ++rear;
        if(rear >= n) rear = rear%n;
        A[rear] = data;
    }
}

void pop_front(){
    if(empty()){
        cout << "[DE-QUEUE IS EMPTY]! No element popped." << endl;
    } else if(front == rear){
        front = rear = -1;
    } else {
        front++;
        if(front >= n) front = front%n;
    }
}

void pop_back(){
    if(empty()){
        cout << "[DE-QUEUE IS EMPTY]! No element popped." << endl;
    } else if(front == rear){
        front = rear = -1;
    } else {
        rear = (rear == 0 && front > rear) ? n - 1 : --rear;
    }
}

void print(){
    if(empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!empty()){
            cout << A[front];
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