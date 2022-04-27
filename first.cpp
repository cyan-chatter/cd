#include <iostream>
#include<vector>
#include<map>
#include<set>
#include<sstream>
#define outv(x)      \
    for (auto i : x) \
    cout << i << " "
using namespace std;
#define str(x) string(1,x)

map<string,vector<string>> gram;
map<string,set<char>> First;
vector<string> T;

string generateFirst(string var){
    if(First.count(var)) return string(First[var].begin(),First[var].end());
    if(var[0]<'A' or var[0]>'Z' ) return str(var[0]);
    vector<string> prods = gram[var];
    for(int i = 0;i<prods.size();i++){
        bool isNull;
        int ind = 0;
        do{
            isNull = false;
            string first = generateFirst(str(prods[i][ind]));
            for(auto j: first){
                if(j!='#')First[var].insert(j);
                else isNull = true;
            };
            if(ind==prods[i].size()-1){
                if(isNull)First[var].insert('#');
                break;
            }
            ind++;
        }while(ind<prods[i].size() and isNull);
    }
    return string(First[var].begin(),First[var].end());
}

int main() {
    int n;
     cout<<"Enter the no. of productions : ";
    cin>>n;
    for(int i = 0;i<n;i++){
        string rhs, lhs, prod;
         cout<<"Enter Lhs and Rhs of Each Production(Lhs Rhs) : ";
        cin>>lhs>>rhs;
        T.push_back(lhs);
        stringstream ss(rhs);
        while(getline(ss,prod,'/')){
            gram[lhs].push_back(prod);
        }
    }
    cout<<"\nVariable \tFirst\n";
    for(auto i:T){
        cout<<i<<"\t\t\t";
        for(auto ch:generateFirst(i)){
            cout<<ch<<", ";
        }cout<<endl;
    }
}