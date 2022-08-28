#include <iostream>
#include <deque>
using namespace std;

deque<int> A;

void print(){
    if(A.empty()){
        cout << "[EMPTY QUEUE]" << endl;
    } else {
        while(!A.empty()){
            cout << A.front();
            A.pop_front();
            if(!A.empty()) cout << " <= ";
        }
        cout << endl;
    }
}

int main(){
    A.push_front(15);
    A.push_front(10);
    A.push_front(5);
    A.push_back(20);
    A.push_back(25);

    A.pop_back();
    A.push_front(2);
    A.pop_front();
    A.pop_back();

    print();
}