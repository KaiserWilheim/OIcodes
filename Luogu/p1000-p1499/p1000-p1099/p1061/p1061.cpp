#include <bits/stdc++.h>
using namespace std;
int a[30],b[30];
int main(){
	int s,t,w,st=1;
	cin>>s>>t>>w;
	for(int i=1;i<=w;i++){
		b[i]=t-(w-i);
	}
	for(int i=1;i<=w;i++){
		char c;
		cin>>c;
		a[i]=c-'a'+1;
		a[0]+=a[i];
	}
	for(int i=1;i<=5;i++){
		st=1;
		for(int j=w;j>=1;j--){
			if(a[j]>=b[j]){
				a[j]=-1;
			}else{
				break;
			}
		}
		for(int j=w;j>=1;j--){
			if((a[j]==-1)&&(a[j-1]!=-1)){
				st=0;
				a[j-1]++; 
				for(int k=j;k<=w;k++){
					a[k]=a[k-1]+1;
				}				
			}
		}
		if(st==1)a[w]++;
		for(int j=1;j<=w;j++){
			char c=a[j]+'a'-1;
			cout<<c;
		}
		cout<<endl;
		if(a[0]==(s+s-w+1)*w/2)return 0;
	}
	return 0;
}
