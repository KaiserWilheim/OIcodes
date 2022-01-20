#include <bits/stdc++.h>
using namespace std;
int main(){
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		long long l,r,ans;
		cin>>l>>r;
		ans=((r+l)%9)*((r-l+1)%9)*5;
		ans%=9;
		cout<<ans<<endl;
	}
	return 0;
}
