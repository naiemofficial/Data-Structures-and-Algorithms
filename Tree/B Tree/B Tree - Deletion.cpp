#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

NODE *maxNode(NODE *root){
    NODE *leafMax = NULL;
    for(int i = 1; i < root->leaf.size(); i++){
        if(root->leaf[i]) leafMax = root->leaf[i];
    }
    if(leafMax){
        return maxNode(leafMax);
    } else {
        return root;
    }
}

int maxValue(NODE *root){
    NODE *leafMax = NULL;
    for(int i = 1; i < root->leaf.size(); i++){
        if(root->leaf[i]) leafMax = root->leaf[i];
    }
    if(leafMax){
        return maxValue(leafMax);
    } else {
        return *max_element(root->key.begin(), root->key.end());
    }
}

int countKeys(NODE *root){
    if(!root || (root && !root->key[0])) return 0;
    int count = 0;
    for(int i = 0; i < root->key.size(); i++){
        if(root->key[i]) count++;
    }
    return count;
}

int searchLeafIndex(NODE* leaf){
    NODE *root = leaf->parent;
    if(root){
        int leafs = root->leaf.size();
        for(int i = 0; i < leafs; i++){
            if(root->leaf[i] == leaf) return i;
        }
    }
    return -1;
}

bool hasLeaf(NODE *root){
    if(!root || (root && !root->leaf[0])) return false;
    for(int i = 0; i < root->leaf.size(); i++){
        if(root->leaf[i]) return true;
    }
    return false;
}

string nodeStatus(NODE *node){
    if(!node){
        return "";
    } else if(!node->parent){
        return "root";
    } else if(node->parent && hasLeaf(node)) {
        return "internal";
    }
    return "leaf";
}

NODE *mergeKey(NODE *from, NODE *to){
    int space = getSpace(to)-1;
    int key;
    for(int i = 0; space < to->key.size(); i++, space++){
        key = from->key[i];
        to->key[space] = from->key[i];
        from->key[i] = 0;
        if(!to->leaf[space]){
            to->leaf[space] = from->leaf[i];
            from->leaf[i] = NULL;
            if(to->leaf[space]) to->leaf[space]->parent = to;
        }
        if(space == to->key.size()-1 || (i < from->key.size()-1 && key && !from->key[i+1])){
            to->leaf[space+1] = from->leaf[i+1];
            from->leaf[i+1] = NULL;
            if(to->leaf[space+1]) to->leaf[space+1]->parent = to;
        }
    }
    to->key = sortNonZero(to->key);
    if(countKeys(from) == 0) delete from;
    return to;
}

NODE *sortLeaf(NODE *node, int index){
    if(!node) return 0;
    for(int i = index; i < node->leaf.size()-1; i++){
        node->leaf[i] = node->leaf[i+1];
        node->leaf[i+1] = 0;
    }
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

NODE *merge(NODE *node){
    if(!node) return 0;
    int minKeys = ceil((float)node->leaf.size()/2)-1; // Minimum Number of Keys
    int leafID = searchLeafIndex(node); // Leaf Index
    
    // Identify Left & Right Child/Node
    NODE *root = node->parent, *LN = NULL, *RN = NULL;
    string node_status = nodeStatus(node); // Detect the Node position
    if(root && leafID != 0) LN = root->leaf[leafID-1]; 
    if(root && leafID != root->leaf.size()-1) RN = root->leaf[leafID+1];

    // Count number of keys
    int CNK = countKeys(node); // CNK = Current Node -> Keys
    int LNK = countKeys(LN);   // LNK = Left Node -> Keys
    int RNK = countKeys(RN);   // RNK = Right Node -> Keys
    
    int space = getSpace(node)-1;
    if(CNK >= minKeys || (node_status == "root" && CNK >= 1)){
        // Do nothing
    } else if(node_status == "root" && CNK == 0){
        NODE *temp = node;
        node = node->leaf[0];
        node->parent = NULL;
        delete temp;
    } else if(root){
        
        // Check minimum number of keys
        if(LNK > minKeys || RNK > minKeys){
            // If Left Child or the Right Child has more than mim=nimum keys
            if(LNK > minKeys){
                int TKey = node->key[space] = root->key[leafID-1];
                root->key[leafID-1] = LN->key[LNK-1];
                LN->key[LNK-1] = 0;
                LN->key = sortNonZero(LN->key);
                node->key = sortNonZero(node->key);
                int TKeyID = searchIndex(node, TKey);
                node = shiftLeaf(node, TKeyID);
                node->leaf[TKeyID] = LN->leaf[LNK];
                node->leaf[TKeyID]->parent = node;
                LN->leaf[LNK] = NULL;
            } else if(RNK > minKeys){
                node->key[space] = root->key[leafID];
                root->key[leafID] = RN->key[0];
                RN->key[0] = 0;
                RN->key = sortNonZero(RN->key);
            }
            node->key = sortNonZero(node->key);
        } else {
            // If Left & Right both child contains equal to minimum number of keys
            if(LN){
                int TKey = node->key[space] = root->key[leafID-1];
                root->key[leafID-1] = 0;
                node->key = sortNonZero(node->key);
                root->key = sortNonZero(root->key);
                int TKeyID = searchIndex(node, TKey);
                node = shiftLeaf(node, TKeyID);
                node->leaf[TKeyID] = NULL;

                node = mergeKey(node, LN);
                root = sortLeaf(root, leafID);
            } else if(RN){
                node->key[space] = root->key[leafID];
                root->key[leafID] = 0;
                node->key = sortNonZero(node->key);
                root->key = sortNonZero(root->key);
                node = mergeKey(RN, node);
                root = sortLeaf(root, leafID+1);
            }
            node = merge(node->parent);
        }
    }
    return node;
}

NODE *deleteKey(NODE *root, int key){
    if(root == NULL || (root && !root->key[0])){
        return 0;
    } else {
        bool matched = (find(root->key.begin(), root->key.end(), key) != root->key.end());
        bool SL = false; // Search if matched key found to the left sub-tree (as per the condition "<=")
        int keyID = matched ? searchIndex(root, key) : -1;
        if(matched) SL = search(root->leaf[keyID], key);
        
        if(matched && !SL){
            if(hasLeaf(root)){
                // If the targeted key found in the root / internal node, replace it with the largest key from the left node
                NODE *max = maxNode(root->leaf[keyID]);
                int maxKey = maxValue(max);
                root->key[keyID] = maxKey;
                // Delete the duplicate key that was used to replace
                return deleteKey(root->leaf[keyID], maxKey);
            } else {
                // If the targeted key found in the leaf node, remove the key then check the node if eligible for merge -> Line #426
                root->key[keyID] = 0;
                root->key = sortNonZero(root->key);
            }
            // Go for merge & check if merge is needed 
            root = merge(root);
            // Always return the root of the whole tree
            while(root->parent) root = root->parent;
            return root;
        } else if(matched && SL){
            return deleteKey(root->leaf[keyID], key);
        } else {
            // Locate the the key path
            int i, keys = root->key.size();
            for(i = 0; i < keys; i++){
                if(key < root->key[i] || (i != keys-1 && !root->key[i+1]) || i == keys-1){
                    break;
                }
            }
            if(root->key[i]){
                if(key < root->key[i]){
                    return deleteKey(root->leaf[i], key);
                } else if(key > root->key[i]){
                    return deleteKey(root->leaf[i+1], key);
                }
            }
        }
    }

    return root;
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
    cout << endl;
}

int main(){
    vector<int> input = {7, 9, 22, 24, 20, 6, 8, 21, 23, 5, 25, 1, 2, 10, 11, 3, 12, 26, 27, 28, 29, 30, 31, 32, 33, 34};
    int order = 5;

    if(int m = validateOrder(input, order)){
        NODE *root = NULL;
        for(int i = 0; i < input.size(); i++){
            root = insert(root, input[i], m);
        }

        cout << "Before deletion" << endl;
        print(root);

        // Delete keys
        root = deleteKey(root, 7);
        root = deleteKey(root, 29);
        root = deleteKey(root, 23);
        root = deleteKey(root, 22);
        root = deleteKey(root, 32);
        root = deleteKey(root, 25);
        root = deleteKey(root, 31);

        cout << endl << "After deletion" << endl;
        print(root);
    }
}