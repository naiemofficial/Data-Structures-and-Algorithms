#include <iostream>
#include <cmath>
using namespace std;

void interpolationSearch(int A[], int n, int key){
    int low = 0, high = n-1, result = 0, attempt = 0;
    while(low <= high && (key >= A[low] && key <= A[high])){
        attempt++;
        if(low == high) {
            if(key == A[low]) result += 1;
            break;
        }

        int index = low + (((double)(high - low) / (A[high] - A[low])) * (key - A[low]));
        if(key == A[index]){
            result = index + 1;
            break;
        }
        if(key > A[index]) low = index+1;
        if(key < A[index]) high = index-1;
    }

    if(result > 0){
        cout << "The element [" << key << "] is matched at the position (" << result << ")" << endl;
    } else {
        cout << "The element [" << key << "] didn't match with any element in the array." << endl;
    }
    cout << "Total attempt(s): " << attempt << endl;
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
    int key = 45;
    interpolationSearch(A, n, key);
}