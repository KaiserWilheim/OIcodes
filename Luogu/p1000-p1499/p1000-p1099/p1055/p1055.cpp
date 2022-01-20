#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
	char s[14];
	int a[11],c;
	scanf("%c-%c%c%c-%c%c%c%c%c-%c",&s[1],&s[2],&s[3],&s[4],&s[5],&s[6],&s[7],&s[8],&s[9],&s[10]);
	for(int i=1;i<=13;){
		if(s[i]=='X'){
			a[i]=10;
		}else{
			a[i]=s[i]-'0';
		}
		i++;
	}
	long b;
	b=a[1]+2*a[2]+3*a[3]+4*a[4]+5*a[5]+6*a[6]+7*a[7]+8*a[8]+9*a[9];
	c=b%11;
	if(c==a[10]){
		cout<<"Right";
	}else{
		char x;
		if(c==10){
			x='X';
		}else{
			x=c+'0';
		}
		printf("%d-%d%d%d-%d%d%d%d%d-%c",a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],x);
	}
	return 0;
}
