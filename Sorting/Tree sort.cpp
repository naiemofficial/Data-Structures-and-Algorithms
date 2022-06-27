#include <iostream>
using namespace std;

struct NODE {
    int key;
    NODE *left;
    NODE *right;
};

NODE *add(NODE *node, int key){
    if(node == 0){
        node = new NODE;
        node->key = key;
        return node;
    } else {
        if(key <= node->key){
            node->left = add(node->left, key);
        } else {
            node->right = add(node->right, key);
        }
        return node;
    }
}

void inorder(NODE *root, int A[], int &i){
    if(root != 0){
        inorder(root->left, A, i);
        A[i++] = root->key;
        inorder(root->right, A, i);
    }
}

void treeSort(int A[], int n){
    if(n > 0){
        NODE *root = 0;
        root = add(root, A[0]);
        for(int i = 1; i < n; i++){
            root = add(root, A[i]);
        }

        int i = 0;
        inorder(root, A, i);
    } else {
        cout << "The array must have one or more elements" << endl;
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
    treeSort(A, n);
    print(A, n);
}