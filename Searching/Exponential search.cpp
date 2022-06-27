#include <iostream>
#include <cmath>
using namespace std;

void exponentialSearch(int A[], int n, int key){
    int result = 0, attempt = 0, i = 1, exp = 1;
    if(n > 0 && A[0] == key) result += 1;
    while(i < n && A[i] < key){
        exp++;
        i *= 2;
    }

    // Binary Search
    int start = i/2, end = i, center, bi = 0;
    while (start <= end){
        bi++;
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

    // [Note: The variables 'exp' and 'bi' is used here to count the search hits/attempts]
    if(result > 0){
        cout << "The element [" << key << "] is matched at the position (" << result << ")" << endl;
    } else {
        cout << "The element [" << key << "] didn't match with any element in the array." << endl;
    }
    cout << "Total exponential attempt(s): " << exp << endl;
    cout << "Binary search attempt(s): " << bi << endl;
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {10, 12, 13, 16, 23, 33, 45, 47, 50, 56, 61, 66, 72, 85, 99}; // Must be a sorted array
    int n = sizeof(A)/sizeof(A[0]);
    print(A, n);

    cout << endl;
    int key = 23;
    exponentialSearch(A, n, key);
}