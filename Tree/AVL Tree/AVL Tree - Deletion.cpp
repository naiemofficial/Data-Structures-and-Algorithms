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

int treeHeight(NODE *root) {
    if (root == NULL){
        return 0;
    } else {
        int left = treeHeight(root->left);
        int right = treeHeight(root->right);
        return max(left, right)+1; 
    }
}

NODE *rotate(NODE *root, string direction, NODE *node, string type){
    if(type == "LL" || type == "RR"){
        if(type == "LL"){
            NODE *temp = node;
            node = node->left;
            temp->left = node->right;
            node->right = temp;
        } else if(type == "RR"){
            NODE *temp = node;
            node = node->right;
            temp->right = node->left;
            node->left = temp;
        }

        // Point/Build link to the parent/root node
        if(direction == "left"){
            root->left = node;
        } else if(direction == "right"){
            root->right = node;
        }
        return root;
    } else if(type == "LR"){
        NODE *temp = node->left->right;
        node->left->right = temp->left;
        temp->left = node->left;
        node->left = temp;
        return rotate(root, direction, node, "LL");
    } else if(type == "RL"){
        NODE *temp = node->right->left;
        node->right->left = temp->right;
        temp->right = node->right;
        node->right = temp;
        return rotate(root, direction, node, "RR");
    } 
    return root;
}

NODE *balance(NODE *root, NODE *node){
    // Calculate the balance factor
    int LH = treeHeight(node->left);
    int RH = treeHeight(node->right);
    int balanceFactor = LH-RH;

    if(!(balanceFactor == -1 || balanceFactor == 0 || balanceFactor == 1)){
        // Validate parent/root node direction
        string direction;
        if(node == root->left){
            direction = "left";
        } else if(node == root->right){
            direction = "right";
        }

        // Check rotation type
        if(node->left && node->left->right){
            return rotate(root, direction, node, "LR");
        } else if(node->right && node->right->left){
            return rotate(root, direction, node, "RL");
        } else if(node->left && node->left->left){
            return rotate(root, direction, node, "LL");
        } else if(node->right && node->right->right){
            return rotate(root, direction, node, "RR");
        } 
    }

    if(node->left) root = balance(root, node->left);
    if(node->right) root = balance(root, node->right);
    return root;
}

NODE *insert(NODE *root, int key){
    if(!root) return createNode(key);
    if(key < root->key){
        root->left = insert(root->left, key);
        root = balance(root, root->left);
    } else if(key > root->key) {
        root->right = insert(root->right, key);
        root = balance(root, root->right);
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
        } else { // If both side have treer/nodes of the key, then get minimum value from the right side or maximum value from the right side
            root->key = min(root->right)->key; // Get minimum value from the right subtree and replace with the current value
            root->right = deleteNode(root->right, root->key); // Delete the replaced/swapped value from the right subtree
        }
    }
    if(root && root->left) root = balance(root, root->left);
    if(root && root->right) root = balance(root, root->right);
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
    int A[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};
    int n = sizeof(A)/sizeof(A[0]);

    // Insertion
    NODE *root = NULL;
    for(int i = 0; i < n; i++){
        if(i == 0){
            root = insert(root, A[i]);
        } else {
            insert(root, A[i]);
        }
    }

    // Deletion
    deleteNode(root, 8);
    deleteNode(root, 7);
    deleteNode(root, 11);
    deleteNode(root, 14);
    deleteNode(root, 17);

    cout << "Print the tree ↴ " << endl;
    cout << "-----------------" << endl;
    print(root);

    cout << endl << endl << "Traverse the tree ↴ " << endl << "Inorder: ";
    inorder(root);
}