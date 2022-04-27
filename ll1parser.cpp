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
map<string,set<char>> Follow;
map<string,int> nT;
map<char,int> T;
string start;

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

string generateFollow(string var){
    if(Follow.count(var)) 
        return string(Follow[var].begin(),Follow[var].end());
    if(var==start)Follow[var].insert('$');
    for(auto prod:gram){
        for(auto rule:prod.second){
            for(int i = 0;i<rule.size();i++){
                if(rule[i]==var[0]){
                    int ind = i+1;
                    bool isNull = false;
                    do{
                        isNull = false;
                        string follow="";
                        if(ind==rule.size()){
                            if(prod.first!=var)
                                follow = generateFollow(prod.first);
                        }else{
                            follow = generateFirst(str(rule[ind]));
                        }
                        for(auto j:follow){
                            if(j!='#')Follow[var].insert(j);
                            else isNull = true;
                        }
                        ind++;
                    }while(ind<=rule.size() and isNull);
                }
            }
        }
    }
    return string(Follow[var].begin(),Follow[var].end());
}

char getT(int x){
    for(auto p:T)
        if(p.second == x)return p.first;
}
string getnT(int x){
    for(auto p:nT)
        if(p.second == x)return p.first;
}

int main() {
    int n,curr = 0;
    
    cout<<"Enter the no. of productions : ";
    cin>>n;
    for(int i = 0;i<n;i++){
        string rhs, lhs, prod;
        cout<<"Enter Lhs and Rhs of Each Production(Lhs Rhs) : ";
        cin>>lhs>>rhs;
        if(i==0)start = lhs;
        nT[lhs] = i;
        stringstream ss(rhs);
        while(getline(ss,prod,'/')){
            for(auto ch:prod){
                if((ch<'A' or ch>'Z') and ch!='#')
                    if(!T.count(ch))T[ch] = curr++;
            }
            gram[lhs].push_back(prod);
        }
        T['$'] = curr;
    }
    vector<vector<int>> table(nT.size(),vector<int>(T.size()));
    int seq=1;
    for(auto prod:gram){
        for(auto rule:prod.second){
            cout<<seq<<". "<<prod.first<<" -> "<<rule<<endl;
            bool isNull = true;
            if(rule[0]!='#')
            for(int i = 0;i<rule.size();i++){
                isNull = false;
                string first = generateFirst(str(rule[i]));
                for(char ch:first){ 
                    if(ch!='#') table[nT[prod.first]][T[ch]] = seq;
                    else isNull = true;
                }
                if(!isNull)break;

            }
            if(isNull){
                for(char ch:generateFollow(prod.first)){ 
                    table[nT[prod.first]][T[ch]] = seq;
                }
            }
            seq++;
        }      
    } 
    cout<<"LL1 Parsing Table : \n\n";   
    cout<<"\t ";
    for(int i = 0;i<T.size();i++){
        cout<<getT(i)<<"\t";
    }cout<<endl;
    cout<<"    __________________________________\n";
    for(int i = 0;i<nT.size();i++){
        cout<<getnT(i)<<"\t|";
        for(int j:table[i])
            if(j!=0)cout<<j<<"\t";
            else cout<<" "<<"\t";
        cout<<endl;
    }
    return 0;
}