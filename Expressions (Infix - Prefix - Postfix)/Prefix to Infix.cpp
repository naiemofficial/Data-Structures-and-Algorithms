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

string infix(string prefix){
    // Remove spaces
    prefix.erase(remove(prefix.begin(), prefix.end(), ' '), prefix.end());

    stack<string> stack;
    string A, B, sum;
    for(int i = prefix.size()-1; i >= 0; i--){
        if(isOperator(prefix[i])){
            if(!stack.empty()){
                string A, B, sum;
                A = stack.top(); stack.pop();
                if(stack.empty()){
                    sum = A + " " + string(1, prefix[i]);
                } else {
                    B = stack.top(); stack.pop();
                    sum = A + " " +prefix[i] + " " + B;
                }
                stack.push(sum);
            }
        } else {
            stack.push(string(1, prefix[i]));
        }
    }
    return (!stack.empty() && stack.top() != "!") ? stack.top() : "!";
}

int main(){
    string prefix = "++-+KL*MN*//*^OPWUVTQ";
    cout << "Prefix: " << prefix << endl;

    string result = infix(prefix);
    if(result == "!"){
        cout << "INPUT: Invalid Expression!" << endl;
    } else {
        cout << "Infix: " << result << endl;
    }
}