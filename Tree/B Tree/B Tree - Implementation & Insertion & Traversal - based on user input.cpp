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

void traverse(NODE *root, string sequence){ // PIP = Preorder, Inorder, Postorder
    if(!root) return;
    for(int i = 0; i < root->key.size(); i++){
        if(sequence == "preorder" && root->key[i] != 0) cout << root->key[i] << " => ";
        traverse(root->leaf[i], sequence);
        if(sequence == "inorder" && root->key[i] != 0) cout << root->key[i] << " => ";
        if(i == root->key.size()-1) traverse(root->leaf[i+1], sequence);
        if(sequence == "postorder" && root->key[i] != 0) cout << root->key[i] << " => ";
    }
}

int treeLevel(NODE *root) {
    if (root == NULL){
        return 0;
    } else {
        vector<int> leaf;
        for(int i = 0; i < root->leaf.size(); i++){
            leaf.push_back(treeLevel(root->leaf[i]));
        }

        int maxVal = *max_element(leaf.begin(), leaf.end());
        return (maxVal+1);
    }
}

void printKeys(NODE *root){
    if(!root) return;
    for(int i = 0; i < root->key.size(); i++){
        if(i == 0) cout << "[";
        if (root->key[i] != 0){
            if(i != 0) cout << ",";
            cout << root->key[i];
        }
        if(i == root->key.size()-1) cout << "] ";
    }
}

void printLevel(NODE *root, int level){
    if (root == NULL) return;
    if (level == 1){
        printKeys(root);
    } else if (level > 1) {
        for(int i = 0; i < root->leaf.size(); i++){
            printLevel(root->leaf[i], level-1);
        }
    }
}
 
void printLevelOrder(NODE *root, int h){
    for(int i = 1; i <= h; i++) {
        cout << "Level-" << i-1 << ": ";
        printLevel(root, i);
        cout << endl; // "=> "
    }
}


void print(NODE *root){
    if(!root) return;
    int level = treeLevel(root);
    cout << "Total level/height of the B Tree: " << level << endl;
    cout << "Traverse the B Tree ↴";
    cout << endl << "----------------------------------------";
    cout << endl << "Level order: " << endl;
    printLevelOrder(root, level);
    cout << endl << endl << "Inorder  : ";
    traverse(root, "inorder");
    cout << endl << "Preorder : ";
    traverse(root, "preorder");
    cout << endl << "Postorder: ";
    traverse(root, "postorder");
}

int main(){
    cout << "Enter the values for B-Tree: " << endl;
    cout << "Enter zero (0) to stop insertion" << endl;
    cout << "----------------------------------" << endl;
    vector<int> input;
    int num, i = 0;
    while(true){
        cout << "Enter the number [" << ++i << "]: ";
        cin >> num;
        if(num){
            input.push_back(num);
        } else {
            break;
        }
    }

    int order;
    cout << endl << "Enter the order of insertion: ";
    cin >> order;
    cout << endl << endl;

    if(int m = validateOrder(input, order)){
        NODE *root = NULL;
        for(int i = 0; i < input.size(); i++){
            root = insert(root, input[i], m);
        }
        print(root);
    }
}