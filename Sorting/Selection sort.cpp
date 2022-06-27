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

void print(int A[], int size){
    for (int i = 0; i < size; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int Array[] = {10, 15, 8, 19, 16, 1, 9, 3, 50, 28};
    selectionSort_ASC(Array, 10); // Parameters: Array, size
    print(Array, 10);
}