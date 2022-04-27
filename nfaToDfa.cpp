#include<iostream>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<iomanip>
#include<string>

using namespace std;

map<vector<int>,vector<int>> nfa_tran;
map<vector<int>,vector<vector<int>>> dfa_tran;
map<vector<int>,bool> vis;

int main()
{
     int nst, fin, in;
     int f[10];
     int inp[2] = {0,1};
     
     cout<<"Using the 0 based indexing\n";
     
     cout<<"\nEnter the number of states : ";
     cin>>nst;

     cout<<"\nEnter number of final states : ";
     cin>>fin;

     cout<<"\nEnter final states : ";
     for(int i=0;i<fin;i++){
          cin>>f[i];
     }
     cout<<"\nEnter initial state : ";
     cin>>in;
     int p,q,r,ntran;   
     cout<<"\nEnter number of transition rules in NFA : ";
     cin>>ntran;     
     cout<<"\n\nDefine transition rules in order : initial state input symbol final state\n : ";
     for(int i=0; i<ntran; i++){
          cin>>p>>q>>r;
          nfa_tran[{p,q}].push_back(r);        
     }

     queue<vector<int>> que;
     que.push({in});
     vis[{in}] = true;
     while(!que.empty()){    
         vector<int> curr = que.front();
         que.pop();
         vector<vector<int>> dfaout(int(sizeof(inp))/sizeof(int));
         for(int i:inp){
            set<int> out;
            for(int j:curr){
                if(nfa_tran.count({j,i})){
                    for(int k:nfa_tran[{j,i}])
                        out.insert(k);     
                }
            }
            vector<int> outp(out.begin(),out.end());
            if(!vis[outp]){
                que.push(outp);
                vis[outp] = true;
            }
            dfaout[i] = outp; 
         }
         dfa_tran[curr] = dfaout;
     }
     cout<<"Transition function of DFA is as follows\n";
     cout<<setw(31)<<left<<"State";
     for(int sym:inp)cout<<setw(31)<<left<<sym;
     cout<<endl;
     for(auto p:dfa_tran){
         cout<<"[";
         string input;
         for(int i:p.first){
             input+='q'; input+=to_string(i); input+= ",";
         }
         input+=']';
         cout<<setw(30)<<left<<input;

         for(auto arr:p.second){
             string output;
             cout<<"[";

             for(int j:arr){
                 output+="q"; output+= to_string(j); output+= ",";
             }
             output += "]";
             cout<<setw(30)<<left<<output;
         }
         cout<<endl;
    }  
    return 0;
}