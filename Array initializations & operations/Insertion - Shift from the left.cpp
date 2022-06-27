#include <iostream>
using namespace std;

void insertion(int A[], int size, int position, int value){
    position = position-1; // convert to index
    if(position >= 0 && position < size){
        for (int i = 0; i < size; i++) {
            if (i >= position) {
                int prev, next;
                if (i == position) {
                    prev = A[i];
                    A[i] = value;
                } else {
                    A[i] = prev;
                    prev = next;
                }
                if (i+1 < size) next = A[i+1];
            }
        }
    } else {
        cout << "Invalid position! The position must be less than or equal to the A length." << endl << endl;
    }
}

void print(int A[], int size){
    for (int i = 0; i < size; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 2, 3, 4, 5};
    insertion(A, 5, 3, 9); // Parameters: Array, size, position, value
    print(A, 5);
}