#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int m[1000+10];
void dfs(int h){
	if(m[h]!=-1){
		return;
	}
	m[h]=1;
	for(int i=1;i<=h/2;i++){
		dfs(i);
		m[h]+=m[i];
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		m[i]=-1;
	}
	dfs(n);
	cout<<m[n];
	return 0;
}
