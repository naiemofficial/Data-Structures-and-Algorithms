#include <iostream>
using namespace std;

void deletion(){
    int size, loop, position, value;

    cout << "Enter the size of array: ";
    cin >> size;
    int A[size];
    for( int i = 0; i < size; i++ ){
        cout << "Enter a value for the position of [" << i+1 << "]: ";
        cin >> A[i];
    }

    cout << endl << "Array is => ";
    for( int i = 0; i < size; i++ ){
        cout << "[" << A[i] << "] ";
    }
    cout << endl;

    cout << "How many values do you want to delete from this array?: ";
    cin >> loop;

    for( int i = 0; i < loop; i++ ){
        cout << endl << "[Delete-"<<i+1<<"] Enter the Postion: " ;
        cin >> position;
        position = position-1;
        if(position >= 0 && position < size){
            for( int x = position; x < size-(i+1); x++ ){
                A[x] = A[x+1];
            }

            cout << "Array is => ";
            for(int y = 0; y < size-(i+1); y++){
                cout << "[" << A[y] << "] ";
            }
            cout << endl;
        }else{
            cout << "Invalid position! The position must be less than or equal to the A length";
            break;
        }
    }
}

int main(){
    deletion();
}