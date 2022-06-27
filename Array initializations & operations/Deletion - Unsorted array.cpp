#include <iostream>
using namespace std;

int deletion(int A[], int size, int position){
    if(position >= 0 && position <= size){
        A[position-1] = A[size-1];
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
    int A[] = {3, 1, 5, 2, 4};
    int size = 5;
    size = deletion(A, size, 3); // Parameters: Array, size, position => the function will return the updated size of arrray
    print(A, size);
}