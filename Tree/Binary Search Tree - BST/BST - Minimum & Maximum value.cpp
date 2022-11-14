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

int minValue(NODE *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root->key;
}
int maxValue(NODE *root){
    while(root->right != NULL){
        root = root->right;
    }
    return root->key;
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

int main(){
    NODE *root = NULL;
    root = insert(root, 5);
    insert(root, 1);
    insert(root, 3);
    insert(root, 6);
    insert(root, 6);
    insert(root, 4);
    insert(root, 2);
    insert(root, 7);

    cout << "Print the tree ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);
    cout << endl;

    cout << "Minimum value: " << minValue(root) << endl;
    cout << "Maximum value: " << maxValue(root) << endl;
}