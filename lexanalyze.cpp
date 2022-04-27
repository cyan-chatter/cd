#include <bits/stdc++.h>
using namespace std;
void IO(string name) {
    freopen((name + ".txt").c_str(), "r", stdin);
}
set<string> keywords, op, delimiters;
bool isConst(string &s) {
    for (auto &c: s) {
        if (c >= '0' and c <= '9') continue;
        return false;
    }
    return true;
}
int main() {
    IO("inputProgramFile");
    keywords = {"if", "else", "float", "int", "while", "case", "switch", "break",
                "catch", "const", "do", "double", "false", "true", "goto", "long", "inline",
                "new", "private", "protected", "public", "return", "static", "short", 
                "struct", "this", "union", "void", "volatile", "typedef", "unsigned", "namespace",
                "volatile", "cout", "cin", "printf", "getline", "scanf", "get", "ifstream", "ofstream", "using"};
    op = {"+", "=", "-", "*", "/", "!", "<", ">", "%", "&", "|", "~", "^"};
    delimiters = {";", "{", "}", "(", ")", ",", ":", "[", "]"};
    map<string, string> lexicalAnalyser;
    while (!cin.eof()) {
        string s;
        cin >> s;
        while (!s.empty() and delimiters.count(string(1, s.back()))) s.pop_back();
        if (s.empty()) continue;
        if (isConst(s)) {
            lexicalAnalyser[s] = "Constant";
            continue;
        }
        bool is_op = true;
        for (auto &c: s) is_op &= op.count(string(1, c));
        string ans;
        if (keywords.count(s)) ans = "Keyword";
        else if (is_op) ans = "Operator";
        else ans = "Identifier";
        lexicalAnalyser[s] = ans;
    }
    for (auto &[a, b]: lexicalAnalyser) cout << a << " is " << b << endl;
    return 0;
}
