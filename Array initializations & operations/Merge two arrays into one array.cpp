#include <iostream>
using namespace std;

int *merge(int A[], int sizeA, int B[], int sizeB){
    int size = sizeA+sizeB, temp = 0;
    int *Array = new int[size];
    for(int i = 0; i < size; i++){
        Array[i] = (i < sizeA) ? A[i] : B[temp];
        if(i >= sizeA) temp++;
    }
    return Array;
}

void print(int A[], int size){
    for (int i = 0; i < size; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 3, 5, 7, 9};
    int B[] = {2, 4, 6, 8, 10};

    int sizeA = sizeof(A)/sizeof(A[0]);
    int sizeB = sizeof(B)/sizeof(B[0]);

    int *merged = merge(A, sizeA, B, sizeB);
    print(merged, (sizeA+sizeB));
}