#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
    vector<int>key;
    vector<NODE*>leaf;
    NODE *parent = NULL;
    NODE(int m){
        key = vector<int>(m-1, 0);
        leaf = vector<NODE*>(m, NULL);
    }
};

NODE *createNode(int m, int key){
    NODE *node = new NODE(m);
    node->key[0] = key;
    return node;
}

vector<int> sortNonZero(vector<int> vect){
    vector<int> temp;
    for(int i = 0; i < vect.size(); i++){
        if(vect[i] != 0){
            temp.push_back(vect[i]);
        }
    }
    sort(temp.begin(), temp.end());
    for(int i = 0; i < vect.size(); i++){
        vect[i] = (i < temp.size()) ? temp[i] : 0;
    }
    return vect;
}

int searchIndex(NODE *node, int key){
    if(node){
        for(int i = 0; i < node->key.size(); i++){
            if(node->key[i] == key) return i;
        }
    }
    return -1;
}

int getSpace(NODE *node){
    if(!node) return 0;
    for(int i = 0; i < node->key.size(); i++){
        if(node->key[i] == 0) return i+1;
    }
    return 0;
}

int getMedian(NODE *node, int key){
    int keys = node->key.size();
    return (keys-1)/2; // -1 for Left biased
}

void removeMedian(NODE *node, int index){
    node->key.erase(node->key.begin()+index);
    node->leaf.erase(node->leaf.begin()+index+1);
}

NODE *shiftLeaf(NODE *node, int index){
    if(!node) return 0;
    for(int i = node->key.size(); i > index; i--){
        node->leaf[i] = node->leaf[i-1];
    }
    node->leaf[index] = NULL;
    return node;
}

int addKey(NODE* node, int key){
    node->key.push_back(key);
    node->leaf.push_back(NULL);
    node->key = sortNonZero(node->key);
    int index = searchIndex(node, key);
    shiftLeaf(node, index+1);
    node->leaf[index+1] = NULL;
    return index;
}

NODE *split(NODE *node, int mid){
    int keys = node->key.size();
    int start = -1;
    for(int i = 0; i < keys; i++){
        if(node->key[i] > node->key[mid]) {
            start = i;
            break;
        }
        if(i == keys-1 && start == -1){
            cout << i << endl;
            return NULL;
        }
    }

    NODE *temp = NULL; int i = 0;
    for(int m = start; m < keys; i++, m++){
        if(i == 0){
            temp = createNode(keys, node->key[m]);
        } else {
            temp->key[i] = node->key[m];
        }
        node->key[m] = 0;
        temp->leaf[i] = node->leaf[m];
        node->leaf[m] = NULL;
        if(temp->leaf[i]) temp->leaf[i]->parent = temp;
    }
    temp->leaf[i] = node->leaf[start+i];
    node->leaf[start+i] = NULL;
    if(temp->leaf[i]) temp->leaf[i]->parent = temp;
    return temp;
}

NODE *insert(NODE *node, int key, int m = 0, bool downStream = true){
    if(key == 0){
        cout << "The key [" << key << "] can't be inserted." << endl;
        return node;
    }
    if(!node) return createNode(m, key);

    if(m == 0) m = node->leaf.size();
    int keys = m-1;
    
    bool L = false, R = false;
    int i;
    for(i = 0; i < keys; i++){
        if(node->key[i] == 0){
            break;
        } else if(downStream == true){
            if(key <= node->key[i] && node->leaf[i]){
                L = true; break;
            } else if(key > node->key[i] &&  node->leaf[i+1] && ((i < keys-1 && node->key[i+1] != 0 && key < node->key[i+1]) || node->key[i+1] == 0 || i == keys-1)){
                R = true; break;
            }
        }
    }

    NODE *root = node->parent;
    if((L || R) && downStream){
        NODE *inserted = NULL, *leafStatus = NULL;
        if(L){
            leafStatus = node->leaf[i];
            inserted = insert(node->leaf[i], key);
            if(leafStatus == NULL) node->leaf[i] = inserted;
        } else if(R){
            leafStatus = node->leaf[i+1];
            inserted = insert(node->leaf[i+1], key);
            if(leafStatus == NULL) node->leaf[i+1] = inserted;
        }
    } else if((i == keys && !(L || R) && downStream) || !downStream){ // Split
        if(downStream) addKey(node, key);
        int mid = getMedian(node, key);
        int median = node->key[mid];
        NODE *Right = split(node, mid);
        removeMedian(node, mid);

        if(node->parent == NULL){
            NODE *root = createNode(m, median);
            root->leaf[0] = node;
            root->leaf[1] = Right;
            node->parent = Right->parent = root;
        } else if(int space = getSpace(root)){
            space--;
            root->key[space] = median;
            root->key = sortNonZero(root->key);
            space = searchIndex(root, median);
            shiftLeaf(root, space+1);
            root->leaf[space+1] = Right;
            Right->parent = root;
        } else {
            int index = addKey(root, median);
            root->leaf[index+1] = Right;
            Right->parent = root;
            root = insert(root, -1, m, false);
        }
    } else if(i < keys && (!L && !R)){ // Insert key >>
        node->key[i] = key;
        node->key = sortNonZero(node->key);
    }

    if(node->parent != root) node = node->parent;
    return node;
}

bool search(NODE *root, int key){
    if(root == NULL || (root && !root->key[0])){
        return false;
    } else {
        bool matched = (find(root->key.begin(), root->key.end(), key) != root->key.end());
        if(matched){
            return true;
        } else {
            int i, keys = root->key.size();
            for(i = 0; i < keys; i++){
                if(key < root->key[i] || (i != keys-1 && !root->key[i+1]) || i == keys-1){
                    break;
                }
            }

            if(root->key[i]){
                if(key < root->key[i]){
                    return search(root->leaf[i], key);
                } else if(key > root->key[i]){
                    return search(root->leaf[i+1], key);
                }
            }
        }
    }
    return false;
}

int validateOrder(vector<int> input, int m){
    int order = m;
    if(order <= 1){
        cout << "Error! Order must be greater than " << m << endl;
        return 0;
    } else if(order == 2){
        m = (2*m)-1;
    }
    if(input.size() < m){
        cout << "Error! Condition(s) not fulfilled " << endl;
        cout << "The number of values must be at least " << m << ", for the order of insertion [" << order << "]" << endl;
        return 0;
    }
    return m;
}

void traverseInorder(NODE *root){
    if(!root) return;
    for(int i = 0; i < root->key.size(); i++){
        traverseInorder(root->leaf[i]);
        if(root->key[i] != 0) cout << root->key[i] << " => ";
        if(i == root->key.size()-1) traverseInorder(root->leaf[i+1]);
    }
}

int main(){
    vector<int> input = {1, 4, 7, 10, 21, 31, 25, 19, 20, 28, 15, 16, 17, 18, 2, 3, 4, 5, 8};
    int order = 3;

    if(int m = validateOrder(input, order)){
        NODE *root = NULL;
        for(int i = 0; i < input.size(); i++){
            root = insert(root, input[i], m);
        }

        cout << "Print the B Tree ↴ " << endl << "-----------------" << endl;
        cout << "Inorder: ";
        traverseInorder(root);
        cout << endl;

        int key = 5;
        cout << endl << "Searching: " << key;
        cout << endl << "Result: ";
        if(search(root, key)){
            cout << "Matched" << endl;
        } else {
            cout << "Not matched" << endl;
        }
    }
}