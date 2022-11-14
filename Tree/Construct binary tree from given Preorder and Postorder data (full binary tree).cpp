// Note: An "unique binary Tree" can't be constructed with preorder and postorder sequence but it will be a "unique full binary tree"
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

NODE *buildTree(int preorder[], int postorder[], int start, int end){
    static int i = 0;
    if (start > end) return 0;
    NODE* root = createNode(preorder[i++]);
    if (start == end) return root;
    int id = search(postorder, start, end, preorder[i]);
    root->left = buildTree(preorder, postorder, start, id);
    root->right = buildTree(preorder, postorder, id+1, end-1);
    return root;
}

void inorder(NODE *root){
    if(!root) return;
    inorder(root->left);
    cout << root->key << " => ";
    inorder(root->right);
}

int main(){
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int n = sizeof(preorder)/sizeof(preorder[0]);

    NODE *root = buildTree(preorder, postorder, 0, n-1);
    cout << "Traverse the tree to ↴" << endl;
    cout << "Inorder: ";
    inorder(root);
}