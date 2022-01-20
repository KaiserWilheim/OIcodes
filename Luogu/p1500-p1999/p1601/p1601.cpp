#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
string a,b;
int c[505];
int main(){
	cin>>a>>b;
	int sa,sb,x;
	sa=a.size();
	sb=b.size();
	if(sa>sb){
		x=sa;
	}else{
		x=sb;
	}
	for(int i=1;i<=sa;i++){
		c[i]+=a[sa-i]-'0';
	}
	for(int i=1;i<=sb;i++){
		c[i]+=b[sb-i]-'0';
	}
	for(int i=1;i<=x;i++){
		if(c[i]>=10){
			c[i++]++;
			c[i]-=10;
		}
	}
	if(c[x++]>0){
		x++;
	}
	for(int i=x-2;i>=1;i--){
		cout<<c[i];
	}
	return 0;
}
