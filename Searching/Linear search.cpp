#include <iostream>
using namespace std;

void linearSearch(int A[], int n, int key){
    int result = 0;
    for(int i = 0; i < n; i++){
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
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 10, 7, 3, 9, 8, 5, 6, 4, 2};
    int n = sizeof(A)/sizeof(A[0]);
    print(A, n);
    int key = 5;
    linearSearch(A, n, key);
}