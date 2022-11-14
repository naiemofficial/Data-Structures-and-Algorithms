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

int search(int data[], int from, int to, int key){
    for(int i = from; i <= to; i++) if(data[i] == key) return i; 
    return -1;
}

NODE *buildTree(int inorder[], int postorder[], int start, int end, int n){
    if (start > end) return 0;
    int id = -1;
    for(int i = n-1; i >= 0; i--){
        id = search(inorder, start, end, postorder[i]);
        if(id >= 0) break;
    }
    NODE* root = createNode(inorder[id]);
    if (start == end) return root;
    root->left = buildTree(inorder, postorder, start, id-1, n-1);
    root->right = buildTree(inorder, postorder, id+1, end, n-1);
    return root; 
}

void preorder(NODE *root){
    if(!root) return;
    cout << root->key << " => ";
    preorder(root->left);
    preorder(root->right);
}

int main(){
    int inorder[]  = {4, 2, 5, 1, 6, 3, 7};
    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int n = sizeof(inorder)/sizeof(inorder[0]);

    NODE *root = buildTree(inorder, postorder, 0, n-1, n);
    cout << "Traverse the tree to ↴" << endl;
    cout << "Preorder: ";
    preorder(root);
}