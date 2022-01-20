#include <bits/stdc++.h>
using namespace std;
long long f[10000010];//,v[10010],w[10010];
int main(){
	int t,m,v,w;
	cin>>t>>m;
	for(int i=1;i<=m;i++){
		cin>>v>>w;
		for(int j=v;j<=t;j++){
			f[j]=max(f[j],f[j-v]+w);
		}
	}
	/*for(int i=1;i<=m;i++){
		for(int j=t;j>=v[i];j--){
			for(int k=1;k*v[i]<=j;k++){
				f[j]=max(f[j],f[j-k*v[i]]+k*w[i]);
			}
		}
	}
	int ans=0;
	for(int i=t;i>=1;i--)ans=max(ans,f[i]);
	cout<<ans<<endl; */
	cout<<f[t]<<endl;
	return 0;
}
