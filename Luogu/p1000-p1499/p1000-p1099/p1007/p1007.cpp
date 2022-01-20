#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
	int l,n,s,maxv=0,minv=0;
	cin>>l;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		minv=max(minv,min(s,l-s+1));
		maxv=max(maxv,max(s,l-s+1));
	}
	cout<<minv<<" "<<maxv;
	return 0;
}
