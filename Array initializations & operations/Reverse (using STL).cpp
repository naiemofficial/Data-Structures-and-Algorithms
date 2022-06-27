#include <iostream>
#include <algorithm>
using namespace std;

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(A)/sizeof(A[0]);
    reverse(A, A+n);
    print(A, n);
}