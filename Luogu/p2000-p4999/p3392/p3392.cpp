#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
int wf[55],bf[55],rf[55]; 
int main(){
	int m,n,ans=99999,r=0,w=0,b=0;
	char a;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a;
			if(a=='W'){
				r++;
				b++;
			}else if(a=='B'){
				r++;
				w++;
			}else if(a=='R'){
				w++;
				b++;
			}
		}
		wf[i]=w;
		bf[i]=b;
		rf[i]=r;
	}
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=n-i-1;j++){
			int tot=wf[i]+bf[n-j]-bf[i]+rf[n]-rf[n-j];
			if(tot<ans){
				ans=tot;
			}
		}
	}
	cout<<ans;
	return 0;
}
