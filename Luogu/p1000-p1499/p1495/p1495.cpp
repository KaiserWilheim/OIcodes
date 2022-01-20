#include <bits/stdc++.h>
using namespace std;
long long ans,sum=1;
int a[12],b[12];
int gcd(int x,int y){
	if(x%y==0){
		return y;
	}else{
		return gcd(y,x%y);
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	ans=b[1];
	for(int i=1;i<n;i++){
		sum=sum*a[i]/gcd(sum,a[i]);
		while(ans%a[i+1]!=b[i+1])ans+=sum;
		//cout<<sum<<endl;
	}
	cout<<ans;
	return 0;
}
