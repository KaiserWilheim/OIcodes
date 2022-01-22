#include <bits/stdc++.h>
using namespace std;
struct per{
	int pos;
	string name;
}f[100010];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>f[i].pos>>f[i].name;
	}
	int idx=0;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		x+=f[idx+1].pos*2;
		if(x==0||x==3){
			idx-=y;
		}else{
			idx+=y;
		}
		if(idx>=n)idx-=n;
		if(idx<0)idx+=n;
	}
	cout<<f[idx+1].name<<endl;
	return 0;
}
