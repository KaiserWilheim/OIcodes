#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
int main(){
	bool t=false;
	double x,y,z;
	cin>>x>>y>>z;
	for(int j=123;j<1000;j++){
		int a=j/100,b=(j%100)/10,c=j%10;
		if((a==b)||(b==c)||(a==c))continue;
		int k=y/x*j,l=z/x*j;
		if(l>=1000)break;
		int d=k/100,e=(k%100)/10,f=k%10;
		if((d==e)||(e==f)||(d==f))continue;
		int g=l/100,h=(l%100)/10,i=l%10;
		if((g==h)||(h==i)||(g==i))continue;
		if((a==d)||(a==e)||(a==f))continue;
		if((a==g)||(a==h)||(a==i))continue;
		if((b==d)||(b==e)||(b==f))continue;
		if((b==g)||(b==h)||(b==i))continue;
		if((c==d)||(c==e)||(c==f))continue;
		if((c==g)||(c==h)||(c==i))continue;
		if((d==g)||(d==h)||(d==i))continue;
		if((e==g)||(e==h)||(e==i))continue;
		if((f==g)||(f==h)||(f==i))continue;
		if((a==0)||(b==0)||(c==0))continue;
		if((d==0)||(e==0)||(f==0))continue;
		if((g==0)||(h==0)||(i==0))continue;
		cout<<j<<" "<<k<<" "<<l<<endl;
		t=true;
	}
	if(t==false){
		cout<<"No!!!";
	}
	return 0;
}
