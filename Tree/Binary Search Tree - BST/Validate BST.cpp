#include <iostream>
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

NODE *insert(NODE *root, int key){
    if(!root) return createNode(key);
    if(key < root->key){
        root->left = insert(root->left, key);
    } else if(key > root->key) { // NOTE: use else conditon only to keep duplicate values
        root->right = insert(root->right, key);
    }
    return root;
}

void print(NODE *root, string indent = "", bool right = true){
    if (root != nullptr) {
        cout << indent;
        if(right){
            cout << (indent.length() == 0 ? "Root╌" : "R╌╌╌╌");
            indent += "      ";
        } else {
            cout << "L╌╌╌╌";
            indent += "┆      ";
        }
        cout << "[" << root->key << "]" << endl;
        print(root->left, indent, false);
        print(root->right, indent, true);
    }
}

bool isBST(NODE *root, NODE * left = NULL, NODE * right = NULL){
    if(root == NULL) return true;
    if(left && left->key > root->key) return false;
    if(right && right->key < root->key) return false;

    bool L = isBST(root->left, left, root);
    bool R = isBST(root->right, root, right);
    return (L && R);
}

void validateBST(bool valid){
    if(valid){
        cout << endl <<  "Valid BST" << endl;
    } else {
        cout << endl <<  "Invalid BST" << endl;
    }
}

int main(){
    // Tree 1
    NODE *root = NULL;
    root = insert(root, 5);
    insert(root, 1);
    insert(root, 3);
    insert(root, 4);
    insert(root, 2);
    cout << "Print the Tree-1 ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);
    validateBST(isBST(root));

    // Tree 2
    NODE *tree2 = createNode(1);
    tree2->left = createNode(2);
    tree2->right = createNode(3);
    cout << endl << endl << "Print the Tree-2 ↴ " << endl;
    cout << "-----------------" << endl;
    print(tree2);
    validateBST(isBST(tree2));
}