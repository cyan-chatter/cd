#include <iostream>
#include<vector>
#include<map>
#define outv(x)      \
    for (auto i : x) \
    cout << i << " "
using namespace std;
int main() {
     map<string,string> gram;
     int n;
    //  cout<<"Enter the no. of productions : ";
    cin>>n;
    for(int i = 0;i<n;i++){
        string rhs, lhs;
        //  cout<<"Enter Lhs and Rhs of Each Production(Lhs Rhs) : ";
        cin>>lhs>>rhs;
        gram[lhs] = rhs;
    }

    map<string,string> newgram;
    cout<<"Grammar after removing Left Recursion :- \n";
    for(auto prod:gram){
        int ind = 0;
        vector<string> alpha,beta;
        string s,lhs = prod.first , rhs = prod.second;
        for(char c:prod.second){
            if(c=='/'){
                if(s=="#") beta.push_back("");
                else if(s[0]==prod.first[0])alpha.push_back(s.substr(1,s.size()-1));
                else beta.push_back(s);
                s.clear();
            }
            else s += c;
        }
        if(s=="#") beta.push_back("");      
        else if(s[0]==prod.first[0])alpha.push_back(s.substr(1,s.size()-1));
        else beta.push_back(s);
        if(alpha.size()){
            string newlhs = lhs;
            newlhs += "'";
            cout<<lhs<<" -> "<<beta[0]<<newlhs;
            for(int i = 1;i<beta.size();i++){
                cout<<" / "<<beta[i]<<newlhs;
            }cout<<endl;
            cout<<newlhs<<" -> "<<alpha[0]<<newlhs;
            for(int i = 1;i<alpha.size();i++){
                cout<<" / "<<alpha[i]<<newlhs;
            }
            cout<<" / "<<"null"<<endl;
        }
        else{
            cout<<lhs<<" -> "<<rhs<<endl;
        }
     }
}
