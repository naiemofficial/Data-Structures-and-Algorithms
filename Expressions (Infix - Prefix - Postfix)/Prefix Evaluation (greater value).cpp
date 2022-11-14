#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
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

bool isInt(float data){
    return ((int)data == data);
}

struct Expression {
    string type;
    bool valid;
};
Expression *expression(string expression){
    Expression *exp = new Expression;
    bool strExp = expression.find_first_not_of("(+-*/^) abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
    bool numExp = expression.find_first_not_of("(+-*/^) 0123456789") == string::npos;
    
    if(strExp && !numExp){
        exp->type = "letter";
    } else if(numExp && !strExp){
        exp->type = "number";
    } else {
        exp->type = "!";
    }
    exp->valid = (strExp || numExp) && (strExp != numExp);
    return exp;
}

string evaluate(string prefix){
    stack<float> stack;
    float A, B, sum;
    string number;

    Expression *exp = new Expression;
    exp = expression(prefix);
    bool error = (!exp->valid || exp->type != "number") ? true : false;

    if(!error){
        for(int i = prefix.size()-1; i >= 0 ; i--){
            char data = prefix[i];
            if(data == ' '){
                if(number.length() > 0) stack.push(stoi(number)); number = ""; 
            } else if(isdigit(data)){
                number = data + number;
            } else if(isOperator(data)){
                if(stack.size() >= 2){
                    float A, B, sum;
                    A = stack.top(); stack.pop();
                    B = stack.top(); stack.pop();
                    sum = calculate(data, A, B);
                    stack.push(sum);
                } else {
                    error = true;
                }
            } else {
                error = true;
            }
            if(error) break;
        }
    }

    string finalResult;
    if(!stack.empty() && stack.size() == 1){
        float result = stack.top();
        finalResult = isInt(result) ? to_string((int)result) : to_string(result); // Check if the result has no fractional
    } else {
        error = true;
    }
    return (error) ? "!" : finalResult;
}

int main(){
    string prefix = "- + 2 * 3 4 / 8 ^ 23 2";
    cout << "Prefix: " << prefix << endl;

    string result = evaluate(prefix);
    result = (result == "!") ? "Invalid Expression!" : result;
    cout << "Prefix evaluated result = " << result << endl;
}