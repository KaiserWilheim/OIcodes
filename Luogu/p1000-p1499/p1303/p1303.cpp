#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
int a[2001],b[2001],c[4000002];
char d[2001],e[2001];
int n,m,l;
int main(){
	cin>>d>>e;
	m=strlen(d);
	n=strlen(e);
	for(int i=1;i<=m;i++)a[i]=d[m-i]-'0';
	for(int i=1;i<=n;i++)b[i]=e[n-i]-'0';
	for(int i=i;i<=m;i++){
		for(int j=1;j<=n;j++){
			c[i+j-1]+=a[i]*b[j];
		}
	}
	l=m+n;
	for(int i=1;i<=l;i++){
		if(c[i]>9){
			c[i+1]+=c[i]/10;
			c[i]%=10;
		}
	}
	while((c[l]==0)&&(l>1))l--; 
	for(int i=l;i>=1;i--){
		cout<<c[i];
	}
	return 0;
}
