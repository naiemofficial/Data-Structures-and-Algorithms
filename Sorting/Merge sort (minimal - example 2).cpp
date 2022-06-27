#include <iostream>
using namespace std;

void merge(int A[], int start, int center, int end){
    int L = center - start + 1;
    int R = end - center;
    int Left[L], Right[R];
    int temp = start;

    for(int i = 0; i < L; i++) Left[i] = A[temp++];
    for(int i = 0; i < L; i++) Right[i] = A[temp++];

    int i = 0 , j = 0;
    temp = start;
    while(!(i >= L && j >= R)) A[temp++] = (((i < L && j < R) && Left[i] <= Right[j]) || (i < L && j >= R)) ? Left[i++] : Right[j++];
}

void mergeSort(int A[], int start, int end){
    if(start >= end) return;
    int center = (start + end) / 2;
    mergeSort(A, start, center);
    mergeSort(A, center+1, end);
    merge(A, start, center, end);
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

    mergeSort(A, 0, size-1);
    print(A, size);
}