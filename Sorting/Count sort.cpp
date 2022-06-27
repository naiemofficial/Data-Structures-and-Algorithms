#include <iostream>
using namespace std;

void countSort(int A[], int n){
    // Create an array and set zero as initial value for all the elements 
    const int stack = 10;
    int count[stack] = {0};
    
    // Store the count of each element to the respective index
    for(int i = 0; i < n; i++){
        count[A[i]]++;
    }

    // Store actual position range for the each element
    for(int i = 1; i < stack; i++){
        count[i] += count[i-1];
    }

    // Create an array and store the sorted elements
    int sorted[n];
    for(int i = n-1; i >= 0; i--){
        sorted[--count[A[i]]] = A[i];
    }

    // Copy sorted array to original array
    for(int i = 0; i < n; i++){
        A[i] = sorted[i];
    }
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {5, 3, 4, 2, 5, 4, 3, 0, 5, 1, 4, 5, 2, 3, 4, 5};
    int n = sizeof(A)/sizeof(A[0]);
    countSort(A, n);
    print(A, n);
}