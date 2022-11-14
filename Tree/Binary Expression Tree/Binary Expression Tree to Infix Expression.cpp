#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

struct NODE {
    string key;
    NODE *left;
    NODE *right;
};
NODE *createNode(string key){
    NODE *node = new NODE;
    node->key = key;
    return node;
}

// Create an stack manually to store tree poiner
class Stack {
    NODE *data;
    Stack *next;
    int n = 0;
    public:
        Stack *front = 0;
        void push(NODE *value){
            Stack *element = new Stack;
            element->data = value;
            element->next = (!front) ? 0 : front;
            front = element;
            n++;
        }
        void pop(){
            if(front){
                Stack *temp = front;
                front = front->next;
                delete temp;
                n--;
            }
        }
        NODE *top(){
            return front->data;
        }
        int size(){
            return n;
        }
        bool empty(){
            return (!n) ? true : false;
        }
};

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

int priority(char data){
    if(data == '^'){
        return 3;
    } else if(data == '*' || data == '/'){
        return 2;
    } else if(data == '+' || data == '-'){
        return 1;
    } else {
        return 0;
    }
}

float calculate(char op, float A, float B){
    float sum = 0.0;
    switch(op){
        case '^':
            sum = pow(A, B);
            break;
        case '/':
            sum = A / B;
            break;
        case '*':
            sum = A * B;
            break;
        case '+':
            sum = A + B;
            break;
        case '-':
            sum = A - B;
            break;
    }
    return sum;
}

string infix(NODE *root){
    float result;
    string error = "!";
    if(root == 0){
        return error;
    } else {
        string left, right;
        if(isOperator(root->key[0]) && root->left && root->right){
            if(isOperator(root->left->key[0]) && priority(root->left->key[0]) >= priority(root->key[0])){
                left = infix(root->left);
            } else {
                left = root->left->key;
            }
            if(isOperator(root->right->key[0]) && priority(root->right->key[0]) >= priority(root->key[0])){
                right = infix(root->right);
            } else {
                right = root->right->key;
            }

            if(left == error || right == error){
                root->key = error;
            } else {
                root->key = left + root->key + right;
            }
        } else if(isOperator(root->key[0]) && (!root->left || !root->right)){
            root->key = error;
        }
        return root->key;
    }
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
    NODE *root = new NODE;                              //                        +
                                                        //                        ↓
    root = createNode("+");                             //          ╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
    root->left = createNode("-");                       //          -                            *
    root->right = createNode("*");                      //          ↓                            ↓
    root->left->left = createNode("A");                 //  ╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮           ╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
    root->left->right = createNode("/");                //  A                /           E                F
    root->right->left = createNode("E");                //                   ↓
    root->right->right = createNode("F");               //              ╭╌╌╌╌╌╌╌╌╌╌╮
    root->left->right->left = createNode("B");          //              B          ^
    root->left->right->right = createNode("^");         //                         ↓
    root->left->right->right->left = createNode("C");   //                      ╭╌╌╌╌╌╮
    root->left->right->right->right = createNode("D");  //                      C     D
    
    
    if(root && root->left && root->right){
        cout << "Print the tree ↴ " << endl;
        cout << "-----------------" << endl;
        print(root);
        cout << endl;

        string result = infix(root);
        if(result != "!"){
            cout << "Infix expression: " << result << endl;
        } else {
            cout << "Error: Invalid Binary Expression Tree" << endl;
        }
    } else {
        cout << "Before conversion, a valid Binary Expression Tree must be contructed" << endl;
    }
}