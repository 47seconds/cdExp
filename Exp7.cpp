#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

enum TokenType {
    KEYWORD, IDENTIFIER, NUMBER, OPERATOR, UNKNOWN
};

struct TableEntry {
    string symbolName;
    string dataType;
    string dataValue;
    int level;
};

class Table {
private:
    unordered_map<string, TableEntry> data;

public:
    void add(const string& symbolName, const string& dataType, const string& dataValue, int level) {
        TableEntry entry = {symbolName, dataType, dataValue, level};
        data[symbolName] = entry;
    }

    TableEntry* find(const string& symbolName) {
        if (data.find(symbolName) != data.end()) {
            return &data[symbolName];
        }
        return nullptr;
    }

    void show() {
        cout << left << setw(10) << "Symbol" << setw(10) << "Data_type" << setw(10) << "Value" << setw(10) << "Scope" << endl << endl;
        for (const auto& entry : data) {
            cout << left << setw(10) << entry.second.symbolName << setw(10) << entry.second.dataType << setw(10) << entry.second.dataValue
                 << setw(10) << entry.second.level << endl;
        }
    }
};

class Parser {
private:
    vector<string> reservedWords = {"int", "float", "return", "if", "else", "while"};

public:
    bool checkReserved(const string& token) {
        for (const string& word : reservedWords) {
            if (token == word) return true;
        }
        return false;
    }

    void analyzeAndFill(const string& sourceCode, Table& table) {
        string currentToken, recentType;
        int currentScope = 0;
        for (size_t idx = 0; idx < sourceCode.length(); ++idx) {
            char ch = sourceCode[idx];
            if (isspace(ch)) continue;
            if (isalpha(ch)) {
                currentToken.clear();
                while (idx < sourceCode.length() && (isalnum(sourceCode[idx]) || sourceCode[idx] == '_')) {
                    currentToken += sourceCode[idx++];
                }
                --idx;
                if (checkReserved(currentToken)) {
                    recentType = currentToken;
                } else if (!recentType.empty()) {
                    table.add(currentToken, recentType, "", currentScope);
                    recentType.clear();
                }
            } else if (isdigit(ch)) {
                currentToken.clear();
                while (idx < sourceCode.length() && isdigit(sourceCode[idx])) {
                    currentToken += sourceCode[idx++];
                }
                --idx;
                table.add("const_" + currentToken, "int", currentToken, currentScope);
            } else if (ch == '{') {
                currentScope++;
            } else if (ch == '}') {
                currentScope--;
            }
        }
    }
};

int main() {
    Table symbolTable;
    Parser lexer;
    string inputCode;
    cout << "Enter code: ";
    getline(cin, inputCode);
    cout << endl;
    lexer.analyzeAndFill(inputCode, symbolTable);
    symbolTable.show();
    return 0;
}
