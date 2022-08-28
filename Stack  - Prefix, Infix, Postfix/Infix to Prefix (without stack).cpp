#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Bracket {
    int open = -1, close = -1,length = 0;
    bool valid = false;
};

bool isBracket(char data){
    return (data == '(' || data == ')');
}

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

bool isOperator(char data){
    return (data == '+' || data == '-' || data == '*' || data == '/' || data == '^');
}

bool isOperand(char data){
    return (data >= 'a' && data <= 'z') || (data >= 'A' && data <= 'Z');
}

int opeartorInfo(vector<string> v, string request = ""){
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
    // Remove spaces
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    
    vector<string> result;
    Bracket *bracket = new Bracket;
    bracket = bracketInfo(infix);
    bool error = (infix == "!") ? true : false;
    string operand = "";

    if(bracket->length && !bracket->valid){
        result.push_back("!");
    } else {
        // Check if the bracket last charecter is operator
        if (bracket->close > 0 && bracket->length > 1 && isOperator(infix[bracket->close-1])){
            swap(infix[bracket->close], infix[bracket->close-1]);
            bracket->close--;
            bracket->length--;
        }
        
        // If infixression starts with operator or first operand has a visible operator
        int initOperator = (infix.length() > 1 && isOperator(infix[0]) && isOperand(infix[1])) ? true : false;
        
        // ----- Split the infixression ----- //
        for (int i = 0; i < infix.length(); i++){
            if(error){
                break;
            } else {
                if(bracket->length > 0 && i == bracket->open){
                    result.push_back(infix.substr(i, bracket->length));
                    i += bracket->length-1;
                } else if(isOperand(infix[i])){
                    operand += string(1, infix[i]) + " ";
                    if(operand.length() > 0 && (i == infix.length()-1 || isOperator(infix[i+1]))){
                        result.push_back(operand);
                        operand = "";
                    }
                } else if(isOperator(infix[i])) {
                    if(i == 0 && initOperator) {
                        operand += string(1, infix[i]) + " ";
                    } else {
                        result.push_back(string(1, infix[i]));
                    }
                }
            }
        }        

                   
        
        // ----- Iterate the vector and process the expression ----- //
        if(!error){
            int operators = opeartorInfo(result, "count");
            for(int i = 0; i <= operators; i++){
                int opID = opeartorInfo(result, "index"); // Operator ID
                if(opID > 0){
                    string vExp = result[opID];
                    Bracket *vBracket = new Bracket;

                    string excludedBracket = vExp;
                    if(vExp[0] == '(' && vExp[vExp.length()-1] == ')'){
                        excludedBracket = vExp.substr(1, vExp.length()-2);
                    }

                    vBracket = bracketInfo(excludedBracket);
                    if(!vBracket->valid && vBracket->length > 0){
                        result[0] = "!";
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
    return concatenateVector(result);
}

int main(){
    string infix = "K+L-M*N+(O^P)*W/U/V*T+Q";
    cout << "Infix: " << infix << endl;
    
    string result = prefix(infix);
    result = (result == "!") ? "Invalid Expression!" : result;
    cout << "Postfix: " << result << endl;
}