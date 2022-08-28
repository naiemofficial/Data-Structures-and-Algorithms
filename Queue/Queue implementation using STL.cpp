#include <iostream>
#include <queue>
using namespace std;

queue<int> A;

void print(){
    if(A.empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!A.empty()){
            cout << A.front();
            A.pop();
            if(!A.empty()) cout << " <= ";
        }
        cout << endl;
    }
}

int main(){
    A.push(5);
    A.push(10);
    A.push(15);
    A.push(20);
    A.push(25);

    A.pop();
    A.pop();

    A.push(35);
    A.push(40);

    print();
}