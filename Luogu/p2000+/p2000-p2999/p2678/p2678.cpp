#include <bits/stdc++.h>
using namespace std;
int cor[50010];
int l=0,r=0,mid,s,n,m;
int chk(int x){
	int now=0,cnt=0;
	for(int i=1;i<=n;i++){
		if(cor[i]-now<mid){
			cnt++;
		}else{
			now=cor[i];
		}
	}
	return cnt<=m;
}
int main(){
	cin>>s>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>cor[i];
		r=max(r,cor[i]-cor[i-1]);
	}
	cor[n+1]=s;
	r=max(r,s-cor[n]);
	while(l<=r){
		mid=(l+r)/2;
		if(chk(mid)){
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<r<<endl;
	return 0;
}
