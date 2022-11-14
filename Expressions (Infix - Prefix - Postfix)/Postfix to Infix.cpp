#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

string infix(string postfix){
    // Remove spaces
    postfix.erase(remove(postfix.begin(), postfix.end(), ' '), postfix.end());

    stack<string> stack;
    for(int i = 0; i < postfix.size(); i++){
        if(isOperator(postfix[i])){
            if(!stack.empty()){
                string A, B, sum;
                A = stack.top(); stack.pop();
                if(stack.empty()){
                    sum = string(1, postfix[i]) + " " + A;
                } else {
                    B = stack.top(); stack.pop();
                    sum = B + " " + postfix[i] + " " + A;
                }
                stack.push(sum);
            }
        } else {
            stack.push(string(1, postfix[i]));
        }
    }
    return (!stack.empty() && stack.top() != "!") ? stack.top() : "!";
}

int main(){
    string postfix = "KL+MN*-OP^W*U/V/T*+";
    cout << "Postfix: " << postfix << endl;

    string result = infix(postfix);
    if(result == "!"){
        cout << "INPUT: Invalid Expression!" << endl;
    } else {
        cout << "Infix: " << result << endl;
    }
}