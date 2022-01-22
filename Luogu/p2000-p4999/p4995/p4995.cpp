#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,c,f,w,d;
ll a[305];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)  cin>>a[i];
    sort(a+1,a+n+1);
    w=n;
    while(f<w){
        d=a[f]-a[w];
        c+=d*d;
        f++;
        d=a[w]-a[f];
        c+=d*d;
        w--;
    }
    cout<<c;
    return 0; 
}
