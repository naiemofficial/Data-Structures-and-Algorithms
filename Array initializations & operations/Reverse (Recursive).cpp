#include <iostream>
using namespace std;

void reverse(int A[], int start, int end){
    if(start >= end) return;
    int swap = A[start];
    A[start] = A[end];
    A[end] = swap;
    reverse(A, start+1, end-1); 
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
    reverse(A, 0, n-1);
    print(A, n);
}