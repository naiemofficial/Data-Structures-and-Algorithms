#include <iostream>
using namespace std;

int deletion(int A[], int size, int position, int value){
    position = position-1; // convert to index
    if(position >= 0 && position < size){
        int prev, next;
        for (int i = 0; i < size; i++) {
            if (i >= position && i < size) {
                A[i] = A[i+1];
            }
        }
        return --size;
    } else {
        cout << "Invalid position! The position must be less than or equal to the A length." << endl << endl;
        return 0;
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
    int size = 5;
    size = deletion(A, size, 3, 9); // Parameters: Array, size, position => the function will return the updated size of arrray
    print(A, size);
}