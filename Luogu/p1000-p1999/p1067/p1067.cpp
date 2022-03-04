#include <bits/stdc++.h>
using namespace std;
int a[110];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<=n;i++){
		cin>>a[i];
	}
	if(a[0]==0){
		goto aaa;
	}else if(a[0]==1){
		cout<<"x^"<<n;
	}else if(a[0]==-1){
		cout<<"-x^"<<n;
	}else if(a[0]>1){
		cout<<a[0]<<"x^"<<n;
	}else{
		cout<<a[0]<<"x^"<<n;
	}
	aaa:;
	for(int i=1;i<n-1;i++){
		if(a[i]==0){
			continue;
		}else if(a[i]==1){
			cout<<"+x^"<<n-i;
		}else if(a[i]==-1){
			cout<<"-x^"<<n-i;
		}else if(a[i]>1){
			cout<<"+"<<a[i]<<"x^"<<n-i;
		}else{
			cout<<a[i]<<"x^"<<n-i;
		}
	}
	if(a[n-1]==0){
		goto aa;
	}else if(a[n-1]==1){
		cout<<"+x";
	}else if(a[n-1]==-1){
		cout<<"-x";
	}else if(a[n-1]>1){
		cout<<"+"<<a[n-1]<<"x";
	}else{
		cout<<a[n-1]<<"x";
	}
	aa:;
	if(a[n]==0){
		return 0;
	}else if(a[n]>0){
		cout<<"+"<<a[n]<<endl;
	}else{
		cout<<a[n]<<endl;
	}
	return 0;
}
