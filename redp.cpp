#include <bits/stdc++.h>

using namespace std;

int i, error;
string inp;

struct RDP {
    void T() {
        F();
        Tprime();
    }

    void E() {
        T();
        Eprime();
    }

    void Eprime() {
        if (inp[i] == '+') {
            i++;
            T();
            Eprime();
        }
    }

    void F() {
        if (isalnum(inp[i]))i++;
        else if (inp[i] == '(') {
            i++;
            E();
            if (inp[i] == ')')
                i++;

            else error = 1;
        } else error = 1;
    }

    void Tprime() {
        if (inp[i] == '*') {
            i++;
            F();
            Tprime();
        }
    }
} rdp;


int main() {

    cout << "Enter input string:\n";
    cin >> inp;

    rdp.E();

    if (i == (int) inp.length() and !error) cout << "Accepted\n";
    else cout << "Rejected\n";

    return 0;
}
