#include <iostream>
using namespace std;

void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int partition(int A[], int start, int end){
    int pivot = A[start];
    int left = start, right = end;
    while(left < right){
        while(A[left] <= pivot) left++;
        while(A[right] > pivot) right--;
        if(left < right) swap(A, A[left], A[right]);
    }
    swap(A, A[start], A[right]);
    return right;
}

void quickSort(int A[], int start, int end){
    if(start < end){
        int p = partition(A, start, end);
        quickSort(A, start, p-1);
        quickSort(A, p+1, end);
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
    quickSort(A, 0, size-1);
    print(A, size);
}