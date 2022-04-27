#include <bits/stdc++.h>
using namespace std;
#define sz(v) (int) v.size()
const int N = 1e3 + 5;

struct Production {
    char lhs;
    vector<string> rhs;
} grammar[N];

int n;
string null;
vector<pair<string, vector<string>>> rightRecursiveGrammar;

void removeLeftRecursion(int i) {
    vector<string> rem, withLHS;
    for (auto &rule: grammar[i].rhs) {
        if (rule[0] == grammar[i].lhs) {
            if (sz(rule) > 1) withLHS.push_back(rule.substr(1));
        } else rem.push_back(rule);
    }
    string nLHS;
    nLHS += grammar[i].lhs;
    if (rem.empty()) rightRecursiveGrammar.emplace_back(nLHS, grammar[i].rhs);
    else {
        nLHS += '1';
        for (auto &s: rem) s += nLHS;
        rightRecursiveGrammar.emplace_back(nLHS.substr(0, 1), rem);
        for (auto &s: withLHS) s += nLHS;
        withLHS.push_back(null);
        rightRecursiveGrammar.emplace_back(nLHS, withLHS);
    }
}

int main() {
    null = "?";

    cout << "Enter number of productions:\n";
    cin >> n;

    for (int x = 0; x < n; x++) {
        cout << "Enter LHS:\n";
        cin >> grammar[x].lhs;
        int y;
        cout << "Enter the number of rules in RHS:\n";
        cin >> y;
        cout << "Enter RHS (each rule separated by a space)\n";
        for (int z = 0; z < y; z++) {
            string rhs;
            cin >> rhs;
            grammar[x].rhs.push_back(rhs);
        }
        removeLeftRecursion(x);
    }

    cout << "Right Recursive Grammar\n";
    for (auto &[lhs, rhs]: rightRecursiveGrammar) {
        cout << lhs << " -> ";
        for (auto &s: rhs) {
            cout << s;
            if (s != rhs.back()) cout << " | ";
            else cout << '\n';
        }
    }

    return 0;
}
