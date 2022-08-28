#include <iostream>
using namespace std;

const int n = 5;
int A[n] = {0}, top = -1;

int full(){
    return (top >= n-1) ? 1 : 0;
}

int empty(){
    return (top == -1) ? 1 : 0;
}

void push(int data){
    if(full()){
        cout << "[QUEUE IS FULL]! Element [" << data << "] not pushed into queue." << endl;
    } else {
        A[++top] = data;
    }
}

void pop(){
    if(empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        top--;
    }
}

void print(){
    if(empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!empty()){
            cout << A[top];
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
    push(30);
    push(33);

    print();
}
