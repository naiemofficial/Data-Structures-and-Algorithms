#include <iostream>
#include <stack>
using namespace std;

struct NODE {
    int key;
    NODE *left;
    NODE *right;
};

NODE *createNode(int key){
    NODE *node = new NODE;
    node->key = key;
    return node;
}

int main(){
    NODE *root;
    root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Print the tree data
    cout << root->key << " => ";
    cout << root->left->key << " => ";
    cout << root->right->key << " => ";
    cout << root->left->left->key << " => ";
    cout << root->left->right->key << " => ";
    cout << root->right->left->key << " => ";
    cout << root->right->right->key << endl;
}