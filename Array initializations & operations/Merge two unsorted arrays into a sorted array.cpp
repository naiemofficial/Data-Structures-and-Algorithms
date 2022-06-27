#include <iostream>
using namespace std;

void selectionSort_ASC(int Array[], int size){
    for(int x = 0; x < size-1; x++){
        int temp = x;
        for(int y = x+1; y < size; y++){
            if(Array[y] < Array[temp]) temp = y;
        }
        if(temp != x){
            int swap = Array[x];
            Array[x] = Array[temp];
            Array[temp] = swap;
        }
    }
}

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
    int A[] = {4, 3, 10, 8, 7};
    int B[] = {2, 1, 6, 5, 9};

    int sizeA = sizeof(A)/sizeof(A[0]);
    int sizeB = sizeof(B)/sizeof(B[0]);

    selectionSort_ASC(A, sizeA);
    selectionSort_ASC(B, sizeB);

    int *merged = merge(A, sizeA, B, sizeB);
    print(merged, (sizeA+sizeB));
}