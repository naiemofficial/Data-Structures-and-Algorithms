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

void traverse(NODE *root, string sequence){
    if(!root) return;
    if(sequence == "preorder") cout << root->key << " => ";
    traverse(root->left, sequence);
    if(sequence == "inorder") cout << root->key << " => ";
    traverse(root->right, sequence);
    if(sequence == "postorder") cout << root->key << " => ";
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

    cout << "Traverse the tree ↴";
    cout << endl << "Inorder: ";
    traverse(root, "inorder");
    cout << endl << "Preorder: ";
    traverse(root, "preorder");
    cout << endl << "Postorder: ";
    traverse(root, "postorder");
}