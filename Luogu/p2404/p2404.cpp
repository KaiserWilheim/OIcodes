#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <utility> 
#include <queue>
using namespace std;
int n,k,ans;
int num[21];
bool pr(int x){
	for(int i=2;i<=sqrt(x)+1;i++){
		if(x%i==0){
			return false;
		}
	}
	return true;
}
void count(int a,int b,int c){
	if(a==k){
		if(pr(b)){
			ans++;
		}
		return;
	}
	for(int i=c;i<n;i++){
		count(a+1,b+num[i],i+1);
		return;
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>num[i];
	}
	count(0,0,0);
	cout<<ans;
	return 0;
}
