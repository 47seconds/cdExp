#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool checkOp(string &op1, string &op2, char op) {
    int operand1 = stoi(op1);
    int operand2 = stoi(op2);

    return (op == '>') ? operand1 > operand2 : operand1 < operand2;
}

bool isValid(string &exp) {
    string op1 = "", op2 = "";
    char op;
    
    int i = 0;
    while (i < exp.length() && !isdigit(exp[i]) && exp[i] != '>' && exp[i] != '<') i++;

    while (i < exp.length() && isdigit(exp[i])) op1 += exp[i++];
    
    while (i < exp.length() && isspace(exp[i])) i++;

    if (i < exp.length() && (exp[i] == '>' || exp[i] == '<')) op = exp[i++];
    else return false;
    
    while (i < exp.length() && isspace(exp[i])) i++;
    
    while (i < exp.length() && isdigit(exp[i])) op2 += exp[i++];
    
    if (op1.empty() || op2.empty()) return false;

    return checkOp(op1, op2, op);
}

int main() {
    string exp;
    cout << "Enter condition: " << endl;
    getline(cin, exp);

    cout << (isValid(exp) ? "Valid" : "Invalid") << endl;

    return 0;
}