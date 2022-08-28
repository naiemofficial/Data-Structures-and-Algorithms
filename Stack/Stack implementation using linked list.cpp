#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE *next;
};

NODE *top;

int empty(){
    return !top;
}

void push(int value){
    NODE *newnode = new NODE;
    newnode->data = value;
    newnode->next = (empty()) ? 0 : top;
    top = newnode;
}

void pop(){
    if(empty()){
        cout << "[QUEUE IS EMPTY]! No element popped." << endl;
    } else {
        NODE *temp = top;
        top = top->next;
        delete temp;
    }
}

void print(){
    if(empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!empty()){
            cout << top->data;
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