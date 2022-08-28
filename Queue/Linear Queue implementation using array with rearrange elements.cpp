// It's an alternative programing of Circular Queue that implemented in Linear Queue.
// More described at the line #80
#include <iostream>
using namespace std;

const int n = 5;
int A[n] = {0}, front = -1, rear = front;

int full(){
    return (rear >= n-1);
}

int empty(){
    return (front == -1);
}

void rearrange(){
    if(front > 0){
        int e = (rear-front)+1; // available elements
        int x = front;
        for (int i = 0; i < e; i++){
            A[i] = A[x++];
            if(i == 0) front = i;
            if(i == e-1) rear = i;
        }
    }
}

void push(int data){
    if(full()){
        cout << "[QUEUE IS FULL]! Element [" << data << "] not pushed into queue." << endl;
    } else {
        rear = (front == -1) ? ++front : ++rear;
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
        rearrange();
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

    /*
     * After dequeuing an element we can't access that position by enqueuing process until the queue is completely empty.
     * From the above example (or previous program) our queue size is 5,
     * we enqueued 5 elements and dequeued 2 element then we should have 2 free spaces to add element.
     * Like if we add an element below after deque an element in the previous program
     * enqueue(30);
     * ↳ It will say [QUEUE IS FULL]! ... ...
     * Because after dequeuing element(s), the existing elements position weren't rearranged,
     * and the last element staying at last index so it says queue is full.
     * To avoid this problem we called rearrange method after every dequeuing an element at the line #43,
     * so existing element will be shifted to the front (or lower index).
     *
     * Now we can enqueue as many elements as have been dequeued.
     */
    push(30);
    push(35);

    print();
}
