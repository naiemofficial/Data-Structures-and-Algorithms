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
    int n;
    cout << "Enter the n of array: ";
    cin >> n;

    int A[n];
    bool sorted = true, asc = false, desc = false;
    for(int i = 0; i < n; i++){
        cout << "Enter the element at the position " << i+1 << ": ";
        cin >> A[i];
    }
    print(A, n);

    cout << endl << "-----------------------------------------" << endl;
    cout << "Note! Enter zero (0) to end the program. " << endl;
    while(true){
        int key;
        cout << "Enter the element to be searched: ";
        cin >> key;
        if(key){
            linearSearch(A, n, key);
            cout << endl << endl;
        } else {
            cout << "Program exited!";
            break;
        }
    }
    
}