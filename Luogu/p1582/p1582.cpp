#include <bits/stdc++.h>
using namespace std;
int c1(int x){
	int sum=0,y=x;
	while(y!=0){
		sum+=y%2;
		y-=y%2;
		y/=2;
	}
	return sum;
}
int main(){
	int n,k,ans=0;
	cin>>n>>k;
    while(c1(n)>k){
    	ans+=(n&-n);
    	n+=(n&-n);
	}
    cout<<ans;
	return 0;
}
