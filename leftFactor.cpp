#include <bits/stdc++.h>
using namespace std;
#define sz(v) (int) v.size()
const int N = 1e3 + 5;

string null;
struct Production {
    string lhs;
    vector<string> rhs;
} grammar[N];
vector<Production> leftFactoredGrammar;
void leftFactor(int i) {
    int j = 0;
    while (1) {
        bool can = true;
        vector<string> v = grammar[i].rhs;
        for (int x = 0; x < sz(v); x++) {
            if (sz(v[x]) == j or v[x][j] != v[0][j]) {
                can = false;
                break;
            }
        }
        if (!can) break;
        ++j;
    }
    if (!j) {
        leftFactoredGrammar.push_back(grammar[i]);
        return;
    }
    string nlhs = grammar[i].lhs;
    nlhs += "1";
    string nrhs = grammar[i].rhs[0].substr(0, j) + nlhs;
    leftFactoredGrammar.push_back({grammar[i].lhs, {nrhs}});
    vector<string> v;
    for (auto &s: grammar[i].rhs) {
        string cs = s.substr(j);
        if (cs.empty()) cs = null;
        v.push_back(cs);
    }
    leftFactoredGrammar.push_back({nlhs, v});
}

int main() {
    null = "?";
    int n;
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
    }
    for (int x = 0; x < n; x++) leftFactor(x);
    cout << "Left factored grammar:\n";
    for (auto &x: leftFactoredGrammar) {
        cout << x.lhs << " -> ";
        for (auto &s: x.rhs) {
            cout << s;
            if (s != x.rhs.back()) cout << " | ";
            else cout << '\n';
        }
    }
    return 0;
}