#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
int main(){
	int n,m;
	long long s=0,r=0;
	cin>>m>>n;
	if(m<n){
		int tmp=n;
		n=m;
		m=tmp;
	}
	for(int i=1;i<=n;i++){
		int a=(n-i+1)*(m-i+1);
		s+=a;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a=(n-i+1)*(m-j+1);
			r+=a;
		}
	}
	r-=s;
	cout<<s<<" "<<r;
	return 0;
}
