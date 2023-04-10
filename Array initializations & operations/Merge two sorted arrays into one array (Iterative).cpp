#include <iostream>
using namespace std;

int *merge(int A[], int sizeA, int B[], int sizeB){
    int size = sizeA+sizeB;
    int *sort = new int[size];
    if(sizeA > 0 && sizeB > 0){
        int i = 0, x = 0, y = 0;
        while(x < sizeA && y < sizeB){
            if(A[x] <= B[y]){
                sort[i++] = A[x++];
            } else {
                sort[i++] = B[y++];
            }
        }
        while(x < sizeA){
            sort[i++] = A[x++];
        }
        while(y < sizeB){
            sort[i++] = B[y++];
        }
    } else {
        cout << "Merge not possible" << endl;
    }
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

    int *merged = merge(A, sizeA, B, sizeB);
    print(merged, (sizeA+sizeB));
}