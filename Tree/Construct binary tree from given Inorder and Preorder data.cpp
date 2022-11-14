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

NODE *buildTree(int inorder[], int preorder[], int start, int end){
    static int pre = 0;
    if (start > end) return 0;
    NODE* root = createNode(preorder[pre++]);
    if (start == end) return root;
    int id = search(inorder, start, end, root->key);
    root->left = buildTree(inorder, preorder, start, id-1);
    root->right = buildTree(inorder, preorder, id+1, end);
    return root;
}

void postorder(NODE *root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " => ";
}

int main(){
    int inorder[]  = {4, 2, 5, 1, 6, 3, 7};
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int n = sizeof(inorder)/sizeof(inorder[0]);

    NODE *root = buildTree(inorder, preorder, 0, n-1);
    cout << "Traverse the tree to ↴" << endl;
    cout << "Postorder: ";
    postorder(root);
}