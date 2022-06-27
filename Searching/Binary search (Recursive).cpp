#include <iostream>
using namespace std;

void binarySearch(int A[], int n, int key){
    int start = 0, end = n-1, center, result = 0, attempt = 0;
    while (start <= end){
        attempt++;
        center = (start + end)/2;
        if(key == A[center]){
            result = center+1;
            break;
        } else if (key > A[center]){
            start = center + 1;
        } else if (key < A[center]){
            end = center - 1;
        }
    }
    
    if(result > 0){
        cout << "The element [" << key << "] is matched at the position (" << result << ")" << endl;
    } else {
        cout << "The element [" << key << "] didn't match with any element in the array." << endl;
    }
    cout << "Total attempt(s): " << attempt;
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Must be a sorted array
    int n = sizeof(A) / sizeof(A[0]);
    print(A, n);

    cout << endl;
    int key = 1;
    binarySearch(A, n, key);
}