#include <bits/stdc++.h>
using namespace std;
long long ans,g,h;
long long exgcd(long long e,long long f,long long &g,long long &h){
	if(!f){
		g=1;
		h=0;
		return e;
	}else{
		ans=exgcd(f,e%f,g,h);
		long long i=g;
		g=h;
		h=i-e/f*h;
		return ans;
	}
}
int main(){
	long long x,y,m,n,l;
	cin>>x>>y>>m>>n>>l;
	long long a=x-y,b=n-m;
	if(b<0){
		b=-b;
		a=-a;
	}
	exgcd(b,l,g,h);
	if(a%ans!=0){
		cout<<"Impossible"<<endl;
	}else{
		cout<<((g*(a/ans))%(l/ans)+(l/ans))%(l/ans);
	}
	return 0;
}
