#include <iostream>
using namespace std;

void countSort(int A[], int n, int pos){
    // Create an array and set zero as initial value for all the elements 
    const int stack = 10;
    int count[stack] = {0};
    
    // Store the count of each element to the respective index
    for(int i = 0; i < n; i++){
        count[(A[i]/pos)%10]++;
    }

    // Store actual position range for the each element
    for(int i = 1; i < stack; i++){
        count[i] += count[i-1];
    }

    // Create an array and store the sorted elements
    int sorted[n];
    for(int i = n-1; i >= 0; i--){
        sorted[--count[(A[i]/pos)%10]] = A[i];
    }

    // Copy sorted array to original array
    for(int i = 0; i < n; i++){
        A[i] = sorted[i];
    }
}

int getMax(int A[], int n){
    int max = A[0];
    for(int i = 1; i < n; i++) if(A[i] > max) max = A[i];
    return max;
}

void radixSort(int A[], int n){
    int max = getMax(A, n);
    for(int pos = 1; max/pos > 0; pos *= 10){
        countSort(A, n, pos);
    }
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {15, 233, 454, 672, 895, 124, 343, 560, 785, 91};
    int n = sizeof(A)/sizeof(A[0]);
    radixSort(A, n);
    print(A, n);
}