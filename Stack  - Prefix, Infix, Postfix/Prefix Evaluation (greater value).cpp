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

string evaluate(string prefix){
    bool error = false;
    bool separator = false, space = true;;
    stack<float> stack;

    float A, B, sum;
    for(int i = prefix.size()-1; i >= 0 ; i--){
        char data = prefix[i];
        if(data == ' '){
            space = true;
            separator = false;
        } else if(isdigit(data)){
            if(!stack.empty() && separator == true){
                A = stack.top(); stack.pop();
                string temp = data + to_string((int)A); // Concatenate with the previous digit
                stack.push(stoi(temp));
            } else {
                stack.push(data-'0'); // Convert to int by using charecter zero (ASCII) or, use stoi(to_string(data))
                if(space) separator = true;
            }
        } else if(isOperator(data)){
            space = separator = false;
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