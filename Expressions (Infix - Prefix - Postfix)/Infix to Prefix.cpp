#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

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
    reverse(infix.begin(), infix.end());
    stack<char> stack;
    string result, number;
    char data;

    Expression *exp = new Expression;
    exp = expression(infix);
    bool error = (!exp->valid) ? true : false;

    // ----- Start Scanning ----- //
    if(!error){
        for(int i = 0; i < infix.length(); i++){
            data = infix[i];
            if(isOperand(data) && exp->type == "alphabetic"){
                result += string(1, data) + " ";
            } else if(isdigit(data) && exp->type == "numeric") {
                number += data;
                if(i == infix.length()-1) result += number + " ";
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
            } else if(isOperator(data) || data == ' '){
                if(number.length() > 0) result += number + " "; number = ""; 
                
                if(isOperator(data)){
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
    string infix = "1-2/3^4+5*6^7";
    cout << "Infix: " << infix << endl;

    string result = prefix(infix);
    if(result == "!"){
        cout << "INPUT: Invalid Expression!" << endl;
    } else {
        cout << "Prefix: " << result << endl;
    }
}