#include <iostream>
using namespace std;

void bubbleSort_ASC(int Array[], int size){
    for (int x = 0; x < size-1; x++) {
        for (int y = 0; y < (size-1-x); y++) {
            if(Array[y] > Array[y+1]){
                int swap = Array[y];
                Array[y] = Array[y+1];
                Array[y+1] = swap;
            }
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
    int Array[] = {6, -1, 7, -5, 15, 3, 5, 20, -8, 12};
    bubbleSort_ASC(Array, 10); // Parameters: Array, size
    print(Array, 10);
}