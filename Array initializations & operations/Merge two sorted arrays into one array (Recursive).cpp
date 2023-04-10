#include <iostream>
using namespace std;

int *merge(int A[], int sizeA, int B[], int sizeB, int *sort, int i = 0, int x = 0, int y = 0){
    if(x < sizeA && y < sizeB){
        if(A[x] <= B[y]){
            sort[i++] = A[x++];
        } else {
            sort[i++] = B[y++];
        }
        return merge(A, sizeA, B, sizeB, sort, i, x, y);
    }

    while(x < sizeA) sort[i++] = A[x++]; 
    while(y < sizeB) sort[i++] = B[y++]; 
    return sort;
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

    int *merged = new int[sizeA + sizeB];
    merge(A, sizeA, B, sizeB, merged);
    print(merged, (sizeA+sizeB));
}