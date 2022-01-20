#include <bits/stdc++.h>
using namespace std;
int num[40];
int main(){
	int n,m,len;
	long long ans=0;
	cin>>n;
	string s;
	cin>>s;
	cin>>m;
	len=s.length();
	for(int i=len-1;i>=0;i--){
		if((s[i]>='A')&&(s[i]<='F')){
			ans+=(s[i]-'A'+10)*pow(n,(len-i))/n;
		}else{
			ans+=(s[i]-'0')*pow(n,(len-i))/n;
		}
	}
	for(int i=1;ans!=0;i++){
		num[i]=ans%m;
		ans=(ans-num[i])/m;
		num[0]++;
	}
	for(int i=num[0];i>0;i--){
		if(num[i]>=10){
			char c=num[i]-10+'A';
			cout<<c;
		}else{
			cout<<num[i];
		}
	}
	cout<<endl;
	return 0;
}
