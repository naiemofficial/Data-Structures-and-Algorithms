#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getExponent(int A[], int n){
    int max = A[0], exponent = 1;
    for(int i = 1; i < n; i++) if(A[i] > max) max = A[i];
    for(int exp = exponent; max/exp > 0; exp *= 10) exponent = exp;
    return exponent;
}

void bucketSort(int A[], int n){
    bool mool = true;
    int total = getExponent(A, n); // Total number of buckets based on exponent of largest number
    vector<vector<int>>bucket(total);

    for(int i = 0; i < n; i++){
        int bkt = A[i]/10;
        bucket[bkt].push_back(A[i]);
    }

    int i = 0;
    for(int x = 0; x < bucket.size(); x++){
        if(bucket[x].size() > 0){
            sort(bucket[x].begin(), bucket[x].end());
            for(int y = 0; y < bucket[x].size(); y++){
                A[i++] = bucket[x][y];
            }
        }
    }
}

void print(int A[], int n){
    for (int i = 0; i < n; i++) {
        cout << "[" << A[i] << "] ";
    }
    cout << endl;
}

int main(){
    int A[] = {1, 255, 15, 233, 45, 0, 625, 67, 785, 83, 999};
    int n = sizeof(A)/sizeof(A[0]);
    bucketSort(A, n);
    print(A, n);
}