#include <bits/stdc++.h>
using namespace std;
long long f[1010]/*[1010]*/,lose[1010],win[1010],use[1010];
int main(){
	int n,x;
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>lose[i]>>win[i]>>use[i];
	}
	/*for(int i=1;i<=n;i++){
		for(int j=0;j<=x;j++){
			if(j-use[i]>=0){
				f[i][j]=max(f[i-1][j]+lose[i],f[i-1][j-use[i]]+win[i]);
			}
		}
	}
	long long ans=0;
	for(int i=0;i<=x;i++){
		ans=max(ans,f[n][i]);
	}*/
	for(int i=1;i<=n;i++){
		for(int j=x;j>=0;j--){
			if(j<use[i]){
				f[j]+=lose[i];
			}else{
				f[j]=max(f[j]+lose[i],f[j-use[i]]+win[i]);
			}
		}
	}
	cout<<5*f[x]<<endl;
	return 0;
}
