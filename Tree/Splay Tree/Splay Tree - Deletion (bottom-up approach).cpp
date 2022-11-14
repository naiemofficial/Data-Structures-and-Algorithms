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

NODE *sPlay(NODE *root, int key){
    if(root == NULL){
        return 0;
    } else if(!root->left && !root->right || key == root->key) {
        return root;
    } else if((root->left && key == root->left->key) || (root->left && key < root->left->key && root->left->left == NULL)){
        NODE *subtree = root->left;
        root->left = NULL;
        NODE *temp = subtree->right;
        subtree->right = root;
        subtree->right->left = temp;
        return subtree;
    } else if((root->right && key == root->right->key) || (root->right && key > root->right->key && root->right->right == NULL)){
        int num = root->key;
        NODE *subtree = root->right;
        root->right = NULL;
        NODE *temp = subtree->left;
        subtree->left = root;
        subtree->left->right = temp;
        return subtree;
    } else if(key < root->key){
        root->left = sPlay(root->left , key);
    } else if(key > root->key){
        root->right = sPlay(root->right, key);
    }
    root = sPlay(root, key);
    return root;
}

NODE *insert(NODE *root, int key){
    if(!root) return createNode(key);
    if(key < root->key){
        NODE *num = root;
        root->left = insert(root->left, key);
        root = sPlay(root, root->left->key);
    } else if(key > root->key) {
        root->right = insert(root->right, key);
        root = sPlay(root, root->right->key);
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
    if(root == NULL){
        cout << "Key [" << key << "] doesn't exist in the tree" << endl;
        return root;
    }

    bool play;
    if(key < root->key){
        play = (root->left && !(root->left && root->left->key == key));
        root->left = deleteNode(root->left, key);
        if(play) root = sPlay(root, root->left->key);
    } else if(key > root->key){
        play = (root->right && !(root->right && root->right->key == key));
        root->right = deleteNode(root->right, key);
        if(play) root = sPlay(root, root->right->key);
    } else if(key == root->key){
        cout << "Key [" << key << "] deleted" << endl;
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
        } else { // If both side have treer/nodes of the key, then get minimum value from the right side or maximum value from the right side
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
    int A[] = {15, 10, 17, 7, 13, 16, 14};
    int n = sizeof(A)/sizeof(A[0]);

    NODE *root = NULL;
    for(int i = 0; i < n; i++){
        if(i == 0){
            root = insert(root, A[i]);
        } else {
            root = insert(root, A[i]);
        }
    }

    cout << "Before deletion" << endl << "Print the tree ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);
    cout << endl << endl;

    // Delete node
    root = deleteNode(root, 7);
    cout << "After deletion" << endl << "Print the tree ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);

    cout << endl << endl << "Traverse the tree ↴ " << endl << "Inorder: ";
    inorder(root);
}