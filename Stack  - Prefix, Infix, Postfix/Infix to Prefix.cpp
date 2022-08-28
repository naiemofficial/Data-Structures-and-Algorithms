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

string prefix(string infix){
    // Remove spaces
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    
    reverse(infix.begin(), infix.end());
    stack<char> stack;
    string result;
    char data;
    bool error = (infix == "!") ? true : false;

    // ----- Start Scanning ----- //
    for(int i = 0; i < infix.length(); i++){
        data = infix[i];
        if(isOperand(data)){
            result += string(1, data) + " ";
        } else if(isBracket(data)){
            if(data == ')'){
                stack.push(data);
            } else if(data == '('){
                while(!stack.empty() && stack.top() != ')') {
                    result += string(1, stack.top()) + " ";
                    stack.pop();
                    if(stack.empty()){
                        error = true;
                        break;
                    }
                }
                if(!stack.empty() && stack.top() == ')') stack.pop();
            }
        } else if(isOperator(data)){
            if(stack.empty() || (!stack.empty() && priority(data) > priority(stack.top()))){
                stack.push(data);
            } else if(priority(data) < priority(stack.top())){
                while(!stack.empty() && priority(data) < priority(stack.top())){
                    result += string(1, stack.top()) + " ";
                    stack.pop();
                }
                stack.push(data);
            } else if(priority(data) == priority(stack.top())){
                stack.push(data);
            }
        }
    }

    if(!error){
        while(!stack.empty()){
            result += stack.top();
            stack.pop();
            if(!stack.empty()) result += " ";
        }
        reverse(result.begin(), result.end());
    } else {
        result = "!";
    }
    return result;
}

int main(){
    string infix = "K+L-M*N+(O^P)*W/U/V*T+Q";
    cout << "Infix: " << infix << endl;
    
    string result = prefix(infix);
    result = (result == "!") ? "Invalid Expression!" : result;
    cout << "Prefix: " << result << endl;
}