#include <iostream>
using namespace std;

void insertionSort(int A[], int size){
    for(int i = 1; i < size; i++){
        int temp = A[i];
        int j = i-1;
        while(j >= 0 && A[j] > temp){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = temp;
    }
}

void print(int A[], int size){
    for (int i = 0; i < size; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 10, 7, 3, 9, 8, 5, 6, 4, 2};
    int size = sizeof(A)/sizeof(A[0]);
    insertionSort(A, size);
    print(A, size);
}