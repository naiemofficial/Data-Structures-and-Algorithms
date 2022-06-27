#include <iostream>
using namespace std;

int main(){
    int A[5] = {10, 20, 30, 40, 50};

    int arrayLength = sizeof(A)/sizeof(A[0]);
    for (int i = 0; i < arrayLength; i++) {
        cout << "[" << A[i] << "] ";
    }
}
