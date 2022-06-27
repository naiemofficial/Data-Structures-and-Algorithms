#include <iostream>
#include <cmath>
using namespace std;

void jumpSearch(int A[], int n, int key){
    int prev = 0, jump = sqrt(n);
    while(key > A[jump-1] && jump < n){
        prev = jump;
        jump += sqrt(n); // or, jump += jump;
        if (jump >= n) break;
    }

    // Linear search
    int result = 0, Li = 0;
    for(int i = prev; i < jump; i++, Li++){
        if(i >= n) break;
        if(A[i] == key){
            result = i+1;
            break;
        }
    }

    if(result > 0){
        cout << "The element [" << key << "] is matched at the position (" << result << ")" << endl;
    } else {
        cout << "The element [" << key << "] didn't match with any element in the array." << endl;
    }
    cout << "Total jump(s): " << jump/int(sqrt(n)) << endl;
    cout << "Linear iteration(s): " << Li << endl;
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {0, 2, 3, 5, 8, 12, 25, 33, 48, 66, 78, 123, 456}; // Must be a sorted array
    int n = sizeof(A)/sizeof(A[0]);
    print(A, n);

    cout << endl;
    int key = 33;
    jumpSearch(A, n, key);
}