#include <iostream>
using namespace std;

int main(){
    int A[5];
    A[0] = 10;
    A[1] = 20;
    A[2] = 30;
    A[3] = 40;
    A[4] = 50;

    int arrayLength = sizeof(A)/sizeof(A[0]);
    for (int i = 0; i < arrayLength; i++) {
        cout << "[" << A[i] << "] ";
    }
}
