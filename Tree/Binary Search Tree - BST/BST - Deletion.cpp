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

NODE *min(NODE *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

NODE *deleteNode(NODE *root, int key){
    if(root == NULL) return root;

    if(key < root->key){
        root->left = deleteNode(root->left, key);
    } else if(key > root->key){
        root->right = deleteNode(root->right, key);
    } else if(key == root->key){
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        } else if(root->left == NULL){
            NODE *temp = root->right;
            delete root;
            return temp;
        } else if(root->right == NULL){
            NODE *temp = root->left;
            delete root;
            return temp;
        } else { // If both side have sub-tree/nodes of the key, then get minimum value from the right side or maximum value from the right side
            root->key = min(root->right)->key; // Get minimum value from the right subtree and replace with the current value
            root->right = deleteNode(root->right, root->key); // Delete the replaced/swapped value from the right subtree
        }
    }
    return root;
}

void inorder(NODE *root){
    if(!root) return;
    inorder(root->left);
    cout << root->key << " => ";
    inorder(root->right);
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
    cout << "Inorder traversal: ";
    inorder(root);

    deleteNode(root, 3);
    cout << endl << endl;
    cout << endl << "After deletion - " << endl << "Print the tree ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);
    cout << "Inorder traversal: ";
    inorder(root);
}