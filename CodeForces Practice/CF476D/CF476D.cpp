#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    cout<<(6*n-1)*k<<endl;
    for(int i=1;i<=n;i++){
        int t=6*(i-1);
        cout<<k*(t+1)<<" "<<k*(t+2)<<" "<<k*(t+3)<<" "<<k*(t+5)<<endl;
    }
    return 0;
}
