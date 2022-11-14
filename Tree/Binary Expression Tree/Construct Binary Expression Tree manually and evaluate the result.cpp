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

bool isInt(float data){
    return ((int)data == data);
}

bool isNumber(string data){
    return data.find_first_not_of(".0123456789") == string::npos;;
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

string evaluate(NODE *root){
    float result;
    string error = "!";
    if(root == 0){
        return error;
    } else {
        string left, right;
        if(isOperator(root->key[0]) && root->left && root->right){
            if(isOperator(root->left->key[0]) && priority(root->left->key[0]) >= priority(root->key[0])){
                left = evaluate(root->left);
            } else {
                left = root->left->key;
            }
            if(isOperator(root->right->key[0]) && priority(root->right->key[0]) >= priority(root->key[0])){
                right = evaluate(root->right);
            } else {
                right = root->right->key;
            }

            if(left == error || right == error){
                root->key = error;
            } else if(isNumber(left) && isNumber(right)){
                result = calculate(root->key[0], stof(left), stof(right));
                root->key = isInt(result) ? to_string((int)result) : to_string(result); // Check if the result has no fractional
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
    root->left->left = createNode("1");                 //  ╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮           ╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
    root->left->right = createNode("/");                //  1                /           5                6
    root->right->left = createNode("5");                //                   ↓
    root->right->right = createNode("6");               //              ╭╌╌╌╌╌╌╌╌╌╌╮
    root->left->right->left = createNode("2");          //              2          ^
    root->left->right->right = createNode("^");         //                         ↓
    root->left->right->right->left = createNode("3");   //                      ╭╌╌╌╌╌╮
    root->left->right->right->right = createNode("4");  //                      3     4
    

    if(root && root->left && root->right){
        cout << "Print the tree ↴ " << endl;
        cout << "-----------------" << endl;
        print(root);
        cout << endl;

        string result = evaluate(root);
        if(result != "!"){
            if(isNumber(result)){
                cout << "Binary Expression Tree Result: " << result << endl;
            } else {
                cout << "Alphabetic expression couldn't be evaluated" << endl;
                cout << "Therefore, the Binary Expression Tree is converted to ↴" << endl;
                cout << "Infix expression: " << result << endl;
            }
        } else {
            cout << "Error: Invalid Binary Expression Tree" << endl;
        }
    } else {
        cout << "Error: Before evaluated, a valid Binary Expression Tree must be contructed" << endl;
    }
}