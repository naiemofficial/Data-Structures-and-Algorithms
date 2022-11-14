#include <iostream>
#include <vector>
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

struct Bracket {
    int open = -1, close = -1,length = 0;
    bool valid = false;
};

Bracket *bracketInfo(string exp){
    Bracket *bracket = new Bracket;    
    bracket->open = exp.find_first_of('(');
    bracket->close = exp.find_last_of(')');
    bracket->length = bracket->close - bracket->open;
    if(~bracket->open && ~bracket->close && (bracket->close > bracket->open)){
        bracket->valid = true;
        ++bracket->length;
    }
    return bracket;
}

bool isBracket(char data){
    return (data == '(' || data == ')');
}

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

int priortiy(vector<string> v, string request = ""){
    int bID, exp, mul, div, add, sub, count = 0;
    bID = exp = mul = div = add = sub = -1;
    for(int i = 0; i < v.size(); i++){
        char opr = (v[i].length() == 1) ? v[i][0] : '\0';
        Bracket *bracket = new Bracket;
        bracket = bracketInfo(v[i]);
        if(!isOperator(opr) && bracket->length > 0 && bracket->valid){
            bID = i;
        } else if(isOperator(opr) && ((bracket->valid && bracket->length > 1 && (i < bracket->open && i > bracket->close)) || (bracket->open == -1 && bracket->close == -1))){
            count++;
            if(exp == -1 && opr == '^') exp = i;
            if(mul == -1 && opr == '*') mul = i;
            if(div == -1 && opr == '/') div = i;
            if(add == -1 && opr == '+') add = i;
            if(sub == -1 && opr == '-') sub = i;
        }
    }

    if(request == "index"){
        if(bID >= 0){
            return bID;
        } else if(exp > 0){
            return exp;
        } else if(mul > 0 || div > 0){
            if(mul > 0 && div > 0){
                return (mul < div) ? mul : div;
            } else {
                return (mul > 0 && div < 0) ? mul : div;
            }
        } else if(add > 0 || sub > 0){
            if(add > 0 && sub > 0){
                return (add < sub) ? add : sub;
            } else {
                return (add > 0 && sub < 0) ? add : sub;
            }
        }
    } else if(request == "count"){
        return count;
    }
    return -1;
}

string concatenateVector(vector<string> data){
    string result;
    bool error = false;
    for(int i = 0; i < data.size(); i++){
        if(data[i][0] == '!'){
            result = "!";
            error = true;
            break;
        } else if(!error){
            if(i == 0 && data[i].length() == 1 && isOperator(data[i][0])) data[i] += " ";
            result.append(data[i]);
        }
    }
    return result;
}


string prefix(string infix){    
    vector<string> result;
    Bracket *bracket = new Bracket;
    Expression *exp = new Expression;
    bracket = bracketInfo(infix);
    exp = expression(infix);
    bool error = (!exp->valid || infix == "!") ? true : false;

    string operand = "", number = "";
    char data;
    if(error || (bracket->length && !bracket->valid)){
        error = true;
    } else {
        // Check if the bracket last charecter is operator
        if (bracket->close > 0 && bracket->length > 1 && isOperator(infix[bracket->close-1])){
            swap(infix[bracket->close], infix[bracket->close-1]);
            bracket->close--;
            bracket->length--;
        }
        
        // If infixression starts with operator or first operand has a visible operator
        int initOperator = (infix.length() > 1 && isOperator(infix[0]) && isOperand(infix[1])) ? true : false;
        
        // ----- Split the infix exression ----- //
        for(int i = 0; i < infix.length(); i++){
            data = infix[i];
            if(bracket->length > 0 && i == bracket->open){
                result.push_back(infix.substr(i, bracket->length));
                i += bracket->length-1;
            } else if(isOperand(data) && exp->type == "alphabetic"){
                operand += string(1, data) + " ";
                if(operand.length() > 0 && (i == infix.length()-1 || isOperator(infix[i+1]))){
                    result.push_back(operand);
                    operand = "";
                }
            } else if(isdigit(data) && exp->type == "numeric") {
                number += data;
                if(i == infix.length()-1) result.push_back(number + " ");
            }  else if(isOperator(data) || data == ' ') {
                if(number.length() > 0) result.push_back(number + " "); number = ""; 

                if(isOperator(data)){
                    if(i == 0 && initOperator) {
                        operand += string(1, data) + " ";
                    } else {
                        result.push_back(string(1, data));
                    }
                }
            } else {
                error = true;
                break;
            }
        }        

                   
        data = '\0';
        // ----- Iterate the vector and process the expression ----- //
        if(!error){
            int operators = priortiy(result, "count");
            for(int i = 0; i <= operators; i++){
                int opID = priortiy(result, "index"); // Operator ID
                if(opID > 0){
                    string vExp = result[opID];
                    Bracket *vBracket = new Bracket;

                    string excludedBracket = vExp;
                    if(vExp[0] == '(' && vExp[vExp.length()-1] == ')'){
                        excludedBracket = vExp.substr(1, vExp.length()-2);
                    }

                    vBracket = bracketInfo(excludedBracket);
                    if(!vBracket->valid && vBracket->length > 0){
                        error = true;
                        break;
                    } else if(vBracket->valid){
                        result[opID] = prefix(excludedBracket);
                    } else {
                        if(opID != 0 && isOperator(vExp[1]) && result.size() == 2) {
                            swap(result[opID], result[opID-1]);
                            return concatenateVector(result);
                        } else if (result.size() >= 2 && vExp.length() == 1 && isOperator(vExp[0])) {
                            if(result.size() == 2 && opID == result.size()-1){
                                swap(result[opID], result[opID-1]);
                            } else {
                                string merge;
                                merge = result[opID] + " " + result[opID - 1] + result[opID + 1];
                                result[opID - 1] = merge;
                                result.erase(result.begin() + opID, result.begin() + opID + 2);
                            }
                        } else if(!vBracket->valid) {
                            result[opID] = prefix(excludedBracket);
                        }
                    }
                }
            }
        }
    }
    // Return result
    return (error) ? "!" : concatenateVector(result);
}

int main(){
    string infix = "K+L-M*N+(O^P)*W/U/V*T+Q";
    cout << "Infix: " << infix << endl;

    string result = prefix(infix);
    if(result == "!"){
        cout << "INPUT: Invalid Expression!" << endl;
    } else {
        cout << "Prefix: " << result << endl;
    }
}