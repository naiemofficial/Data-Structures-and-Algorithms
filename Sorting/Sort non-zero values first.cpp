#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> sortNonZero(vector<int> vect){
    vector<int> temp;
    for(int i = 0; i < vect.size(); i++){
        if(vect[i] != 0){
            temp.push_back(vect[i]);
        }
    }
    sort(temp.begin(), temp.end());
    for(int i = 0; i < vect.size(); i++){
        vect[i] = (i < temp.size()) ? temp[i] : 0;
    }
    return vect;
}

void print(vector<int> vect){
    for(int i = 0; i < vect.size(); i++){
        cout << vect[i];
        if(i != vect.size()-1) cout  << " => ";
    }
    cout << endl;
}

int main(){
    vector<int> A = {3, 0, 1, 0, 5, 0, 2};
    cout << "Before: "; print(A);
    A = sortNonZero(A);
    cout << "After : "; print(A);
}