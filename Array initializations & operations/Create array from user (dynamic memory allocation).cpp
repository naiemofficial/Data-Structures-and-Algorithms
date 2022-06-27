#include <iostream>
using namespace std;

int main(){
    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    int *A = new int [n]; // Memory allocation
    for (int i = 0; i < n; i++){
        cout << "Enter the value of index " << i << ": ";
        cin >> A[i];
    }

    cout << endl;

    for (int i = 0; i < n; i++){
        cout << "[" << A[i] << "] ";
    }
    delete A; // Memory deallocation
    
}