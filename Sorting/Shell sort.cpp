#include <iostream>
using namespace std;

void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void shellSort(int A[], int n){
    for(int gap = n/2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            int j, temp = A[i];
            for(j = i; j >= gap && A[j-gap] > temp; j -= gap){
                A[j] = A[j-gap];
            }
            A[j] = temp;
        }
    }
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 10, 7, 3, 9, 8, 5, 6, 4, 2};
    int n = sizeof(A)/sizeof(A[0]);
    shellSort(A, n);
    print(A, n);
}