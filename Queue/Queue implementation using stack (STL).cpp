#include <iostream>
#include <stack>
using namespace std;

stack<int> A, B;

void push(int data){
    A.push(data);
}

void pop(){
    if(A.empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        while(!A.empty()){
            B.push(A.top());
            A.pop();
        }

        B.pop();
        while(!B.empty()){
            A.push(B.top());
            B.pop();
        }
    }
}

void print(){
    if(A.empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!A.empty()){
            B.push(A.top());
            A.pop();
        }
        while(!B.empty()){
            cout << B.top();
            B.pop();
            if(!B.empty()) cout << " <= ";
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