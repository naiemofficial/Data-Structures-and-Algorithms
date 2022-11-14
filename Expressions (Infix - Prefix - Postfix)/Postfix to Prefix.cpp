#include <iostream>
#include <stack>
using namespace std;

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

string prefix(string postfix){
    stack<string> stack;
    string data;
    for(int i = 0; i < postfix.size(); i++){
        data = postfix[i];
        if(isOperand(data[0])){
            stack.push(data);
        } else if (isOperator(data[0])){
            if(!stack.empty()){
                string A, B, sum;
                A = stack.top(); stack.pop();
                if(stack.empty()){
                    sum = data + " " + A;
                } else {
                    B = stack.top(); stack.pop();
                    sum = data + " " + B + " " + A;
                }
                stack.push(sum);
            }
        } else {
            stack.push("!");
            break;
        }
    }
    return (!stack.empty() && stack.top() != "!") ? stack.top() : "!";
}

int main(){
    string postfix = "KL+MN*-OP^W*U/V/T*+Q+";
    cout << "Postfix: " << postfix << endl;

    string result = prefix(postfix);
    if(result == "!"){
        cout << "INPUT: Invalid Expression!" << endl;
    } else {
        cout << "Prefix: " << result << endl;
    }
}