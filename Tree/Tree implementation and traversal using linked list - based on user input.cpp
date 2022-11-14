#include <iostream>
#include <stack>
using namespace std;

struct NODE {
    int key;
    NODE *left;
    NODE *right;
};

NODE *createNode(string state = ""){
    int data;
    if(state == "root") cout << "Enter a value for the root node: "; 
    cin >> data;
    if(!data) return 0;

    NODE *node = new NODE;
    node->key = data;

    string nodeFor = (state == "root") ? state + " node" : to_string(data);
    cout << "Enter a value for the left child of " << nodeFor << ": ";
    node->left =  createNode();
    cout << "Enter a value for the right child of " << nodeFor << ": ";
    node->right =  createNode();
    return node;
}

void preorder(NODE *root){
    if(!root) return;
    cout << root->key << " => ";
    preorder(root->left);
    preorder(root->right);
}

int main(){
    NODE *root;
    cout << "Enter zero (0) to stop input" << endl;
    root = createNode("root");

    cout << endl << "Traverse the tree ↴";
    cout << endl << "Preorder: ";
    preorder(root);
}