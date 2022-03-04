#include <bits/stdc++.h>
using namespace std;
int num[4600];
int main(){
	int n,l=1;
	cin>>n;
	memset(num,0,4600);
	num[1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l;j++){
			num[j]*=2;
		}
		for(int j=1;j<=l;j++){
			if(num[j]>=10){
				num[j+1]++;
				num[j]=num[j]%10;
			}
			if(num[l+1]!=0)l++;
		}
	}
	if(num[1]==0){
		num[2]--;
		num[1]+=9;
	}else{
		num[1]--;
	}
	for(int i=l;i>=1;i--){
		cout<<num[i];
	}
	return 0;
}
