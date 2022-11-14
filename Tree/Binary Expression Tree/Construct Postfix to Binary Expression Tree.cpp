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
    NODE *node = 0;
    node = new NODE;
    node->key = key;
    node->left = node->right = 0;
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

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

bool isBracket(char data){
    return (data == '(' || data == ')');
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

// Check and validate the type of expression
struct Expression {
    string type;
    bool valid;
};
Expression *expression(string expression){
    Expression *exp = new Expression;
    bool strExp = expression.find_first_not_of("(+-*/^) abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
    bool numExp = expression.find_first_not_of("(+-*/^) 0123456789") == string::npos;
    
    if(strExp && !numExp){
        exp->type = "alphabetic";
    } else if(numExp && !strExp){
        exp->type = "numeric";
    } else {
        exp->type = "!";
    }
    exp->valid = (strExp || numExp) && (strExp != numExp);
    return exp;
}

NODE *binaryExp(string postfix){
    Stack *stack = new Stack;
    string number;

    Expression *exp = new Expression;
    exp = expression(postfix);
    bool error = (postfix == "!" || !exp->valid) ? true : false;
    
    if(!error){
        for(int i = 0; i < postfix.length(); i++){
            char data = postfix[i];
            if(isOperand(data) && exp->type == "alphabetic"){
                stack->push(createNode(string(1, data)));
            } else if(isdigit(data) && exp->type == "numeric"){
                number += data;
            } else if(isOperator(data) || data == ' '){
                if(number.length() > 0 && exp->type == "numeric") stack->push(createNode(number)); number = "";
                if(isOperator(data)){
                    if(stack->size() >= 2){
                        NODE *subTree = new NODE;
                        subTree->key = string(1, data);
                        subTree->right = stack->top(); stack->pop();
                        subTree->left = stack->top(); stack->pop();
                        stack->push(subTree);
                    } else {
                        return 0;
                        break;
                    }
                }
            }
        }
    }
    return (stack->size() == 1) ? stack->top() : 0;
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
    string name = "Postfix";
    string postfix = "1 2 3 4 ^ / - 5 6 * +";
    cout << name << ": " << postfix << endl;

    Expression *express = new Expression;
    express = expression(postfix);
    bool error = (!express->valid) ? true : false;
    if(!error){
        NODE *binaryTree = binaryExp(postfix);
        if(binaryTree && binaryTree->left && binaryTree->right){
            cout << endl << "Print the tree ↴ " << endl;
            cout << "-----------------" << endl;
            print(binaryTree);
            cout << endl;
            
            if(express->type == "numeric"){
                string result = evaluate(binaryTree);
                cout << "Binary Expression Tree Result: " << result << endl;
            } else {
                express->type[0] = toupper(express->type[0]);
                cout << express->type << " expression can't be evaluated." << endl;
                cout << "But the " << name << " expression constructed as a Binary Expression Tree" << endl;
            }
        } else {
            cout << "Error: unable to construct Binary Expression Tree" << endl;
            if(express->type == "numeric") cout << "Make sure the expression contains <space> between numbers & operator(s)" << endl;
        }
    }
    if(error) cout << "INPUT: Invalid Expression!" << endl;
}