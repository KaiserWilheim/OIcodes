#include <bits/stdc++.h>
using namespace std;
int mem[30000002];
int f(long long i,long long p){
	if(mem[i])
		return mem[i];
	if(i==1){
		return mem[1]=1;
	}else{
		return mem[i]=((p-p/i)*f(p%i,p))%p;
	}
}
int main(){
	long long n,p;
	cin>>n>>p;
	for(int i=1;i<=n;i++){
		cout<<f(i,p)<<'\n';
	}
	return 0;
}
