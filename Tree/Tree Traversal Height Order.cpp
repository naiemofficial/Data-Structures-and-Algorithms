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

int treeLevel(NODE *root) {
    if (root == NULL){
        return 0;
    } else {
        int left = treeLevel(root->left);
        int right = treeLevel(root->right);
        return max(left, right)+1;
    }
}

void traverse(NODE *root, int level, bool init = false){
    if(!root) return;
    if(level == 1) cout << root->key << " => ";
    for(int i = level; i >= 1 ; i--){
        traverse(root->left, i-1);
        traverse(root->right, i-1);
    }
    if(init) cout << root->key << " => ";
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

    int level = treeLevel(root);
    cout << "Traverse the tree ↴";
    cout << endl << "Height order: ";
    traverse(root, level, true);
}