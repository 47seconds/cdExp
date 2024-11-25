#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool validateString(unordered_map<char, vector<string>> grammer, int &i, string inp, char stSym) {
    for (auto rule : grammer[stSym]) {
        int prev = i;
        bool isValid = true;

        for (char symbol : rule) {
            if (symbol >= 'A' && symbol <= 'Z') {
                if (!validateString(grammer, i, inp, symbol)) {
                    isValid = false;
                    break;
                }
            } else if (symbol == inp[i]) {
                i++;
            } else {
                isValid = false;
                break;
            }
        }

        if (isValid && i == inp.size()) return true;
        i = prev;
    }
    return false;
}

int main() {
    unordered_map<char, vector<string>> grammer;
    int rules;
    char stNTer;

    cout << "Grammar Validator:" << endl;
    cout << "No. of rules in grammer: ";
    cin >> rules;

    for (int i = 0; i < rules; i++) {
        char nter;
        int prodCount;

        cout << "Enter the Non-terminal for rule: " << (i + 1) << ": ";
        cin >> nter;

        if (!i) stNTer = nter;

        cout << "No. of productions for " << nter << ": ";
        cin >> prodCount;
        cout << "Productions for " << nter << " (space separated): ";

        for (int j = 0; j < prodCount; j++) {
            string prod;
            cin >> prod;
            grammer[nter].push_back(prod);
        }
    }

    string inp;
    cout << "Enter the string to be validated: ";
    cin >> inp;

    int i = 0;
    bool isValid = validateString(grammer, i, inp, stNTer);

    string res = (isValid) ? "The input string follows the grammar." : "The input string doesn't follow the grammar.";
    cout << res << endl;

    return 0;
}
