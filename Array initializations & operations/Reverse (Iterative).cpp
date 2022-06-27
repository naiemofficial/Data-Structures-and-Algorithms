#include <iostream>
using namespace std;

void reverse(int A[], int n){
    if(n > 1){
        int j = n-1;
        for(int i = 0; i < j; i++, j--){
            int swap = A[i];
            A[i] = A[j];
            A[j] = swap;
        }
    } else {
        cout << "Array must have more than 1 elements" << endl;
    }
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(A)/sizeof(A[0]);
    reverse(A, n);
    print(A, n);
}