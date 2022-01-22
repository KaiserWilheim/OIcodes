#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
bool f[10010];
void suv(int p,int m){
    if(p==0) {
        if(!f[m]) ans++;
        f[m]=1;
    }
    else{
        for(int r=p;r>=1;r--) suv(p-r,r*(p-r)+m);
    }
    return;
}
int main(){
    cin>>n;
    suv(n,0);
    cout<<ans;
    return 0;
}
