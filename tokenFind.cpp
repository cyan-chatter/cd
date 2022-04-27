#include<bits/stdc++.h>
#include<sstream>

using namespace std;

set<string> keywords = {"if", "else", "float", "int", "while", "case", "switch", "break",
                        "catch", "const", "do", "double", "false", "true", "goto", "long", "inline",
                        "new", "private", "protected", "public", "return", "static", "short",
                        "struct", "this", "union", "void", "volatile", "typedef", "unsigned",
                        "volatile", "cout", "cin", "printf", "getline", "scanf", "get", "ifstream", "ofstream"};
set<string> op = {"+", "=", "-", "*", "/", "!", "<", ">", "%", "&", "|", "~", "^"};
set<string> delimiters = {";", "{", "}", "(", ")", ",", ":", "[", "]"};

char type[1000];

void parse(string &s) {
    string token;
    int k = 0;
    for (auto &c: s) {
        if ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (c >= '0' and c <= '9')) token += c;
        else {
            if (!token.empty()) {
                if (keywords.count(token)) type[k++] = 'K';
                else type[k++] = isdigit(token[0]) ? 'N' : 'I';
            }
            token.clear();
            if (c == ' ') continue;
            if (op.count(string(1, c))) type[k++] = 'O';
            else if (delimiters.count(string(1, c))) type[k++] = 'S';
        }
    }
    map<char, int> cnt;
    for (int x = 0; x < s.length(); x++) {
        cnt[type[x]]++;
        if (type[x] == 'O' or type[x] == 'N') {
            while (x + 1 < s.length() and type[x + 1] == type[x]) x++;
        }
    }

    cout << "No. of Keywords : " << cnt['K'] << "\n";
    cout << "No. of Special Characters :" << cnt['S'] << "\n";
    cout << "No. of Identifiers : " << cnt['I'] << "\n";
    cout << "No. of Operators : " << cnt['O'] << "\n";
    cout << "No. of Numbers : " << cnt['N'] << "\n";
    cout << "No. of Total No. of Tokens : " << (cnt['K'] + cnt['S'] + cnt['I'] + cnt['O'] + cnt['N']);
}

int main() {
    ifstream t("input.txt");
    stringstream ss;
    ss << t.rdbuf();
    string s = ss.str();
    cout << "Program:\n";
    cout << s << "\n";
    for (int i = 0; i < 100; i++)cout << '.';
    cout << "\n";
    parse(s);

    return 0;
}
