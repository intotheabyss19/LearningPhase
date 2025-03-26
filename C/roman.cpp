#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin>>s;
    map<char,int> m = {{'M',1000},{'I',1},{'C',100},{'X',10},{'V',5},{'L',50},{'D',500}};
    int ans =0;
    for(int i =0;i<s.size()-1;i++)
    {
        if(m[s[i]]<m[s[i+1]])
        {
            ans =ans -m[s[i]];
        }
        else
        {
            ans+=m[s[i]];
        }
    }
    ans = ans+m[s[s.size()-1]];
    cout<<ans;
}

