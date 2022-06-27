#include <iostream>
using namespace std;

void swap(int A[], int min, int max){
    int temp = A[max];
    A[max] = A[min];
    A[min] = temp;
}

void heapify(int A[], int n, int i){
    int large = i;
    int left = (2*i)+1;
    int right = (2*i)+2;
    
    if(left < n && A[left] > A[large]) large = left;
    if(right < n && A[right] > A[large]) large = right;
    if(large != i){
        swap(A, i, large);
        heapify(A, n, large);
    }
}

void heapSort(int A[], int n){
    for(int i = (n/2)-1; i >= 0; i--){
        heapify(A, n, i);
    }
    for(int i = n -1; i > 0; i--){
        swap(A, 0, i);
        heapify(A, i, 0);
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
    heapSort(A, size);
    print(A, size);
}