#include<bits/stdc++.h>
using namespace std;
int ans[10];
int main(){
    int n,maxn=0;
    cin>>n;
    while(n){
        ans[++ans[0]]=n%10;
        maxn=max(maxn,ans[ans[0]]);
        n/=10;
    }
    cout<<maxn<<endl;
    for(int i=1;i<=maxn;i++){
        bool flag=false;
        for(int j=ans[0];j>0;j--){
            if(ans[j]>0){
                ans[j]--;
                cout<<1;
                flag=true;
            }else{
                if(flag)cout<<0;
            }
        }
        cout<<" ";
    }
    cout<<endl;
    return 0;
}
