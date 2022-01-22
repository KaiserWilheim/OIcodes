#include<bits/stdc++.h>
using namespace std;
map<string,string>p;
string find(string x)
{
    if(x!=p[x]) 
        p[x]=find(p[x]);
    return  p[x];
}
string s,pre;
int main()
{
    char ch;
    cin>>ch;
    while(ch!='$')
    {
        cin>>s;
        if(ch=='#')
        {
            pre=s;
            if(p[s]=="") p[s]=s;
        }
        else if(ch=='+')
            p[s]=pre;
        else 
            cout<<s<<' '<<find(s)<<endl;    
        cin>>ch;
    }
    return 0;
}
