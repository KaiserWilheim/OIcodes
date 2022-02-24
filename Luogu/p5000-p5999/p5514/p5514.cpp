#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,ans;
   	cin>>n;
   	cin>>ans;
    for(int i=2;i<=n;i++){
    	int a;
    	cin>>a;
    	ans=ans^a;
	}
	cout<<ans<<endl;
    return 0;
}
