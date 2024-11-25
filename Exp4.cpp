#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool isOpChar(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void generateTAC(const string& exp) {
    int temp = 1;
    string opSt[256];
    string oprdSt[256];
    int opTop = -1, oprdTop = -1;

    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == ' ')
            continue;

        if (isalnum(exp[i])) {
            int pos = i;
            string currOp;
            while (pos < exp.length() && isalnum(exp[pos])) {
                currOp += exp[pos];
                pos++;
            }
            i = pos - 1;
            oprdSt[++oprdTop] = currOp;
        }
        else if (isOpChar(exp[i])) {
            opSt[++opTop] = exp[i];
        }
    }

    while (opTop >= 0 && oprdTop >= 1) {
        string tempVar = "t" + to_string(temp++);
        cout << tempVar << " = " << oprdSt[oprdTop - 1] << " "
             << opSt[opTop] << " " << oprdSt[oprdTop] << endl;
        oprdSt[oprdTop - 1] = tempVar;
        opTop--;
        oprdTop--;
    }
}

int main() {
    cout << "Hardcoded:" << endl;
    cout << "Expression: x = a + b*2" << endl;
    cout << "Three Address Code:" << endl;
    generateTAC("x = a + b*2");
    cout << endl;

    cout << "User Input:" << endl;
    string userExpr;
    cout << "Enter Expression: ";
    getline(cin, userExpr);
    cout << "Three Address Code:" << endl;
    generateTAC(userExpr);
    cout << endl;

    return 0;
}
