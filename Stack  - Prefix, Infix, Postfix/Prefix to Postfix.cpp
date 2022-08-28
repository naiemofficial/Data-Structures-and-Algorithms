#include <iostream>
#include <stack>
using namespace std;

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

string postfix(string prefix){
    stack<string> stack;
    string data;
    for(int i = prefix.size()-1; i >= 0; i--){
        data = prefix[i];
        if(isOperand(data[0])){
            stack.push(data);
        } else if (isOperator(data[0])){
            if(!stack.empty()){
                string A, B, sum;
                A = stack.top(); stack.pop();
                if(stack.empty()){
                    sum = A + " " + data;
                } else {
                    B = stack.top(); stack.pop();
                    sum = A + " " + data+ " " + B;
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
    string prefix = "++-+KL*MN*//*^OPWUVTQ";
    cout << "Prefix: " << prefix << endl;

    string result = postfix(prefix);
    result = (result == "!") ? "Invalid Expression!" : result;
    cout << "Postfix: " << result << endl;
}