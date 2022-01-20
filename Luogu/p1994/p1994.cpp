#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int c=0,h=0,o=0;
	for(int i=0;i<s.length();i++){
		if(s[i]=='C'){
			if((s[i+1]=='C')||(s[i+1]=='H')||(s[i+1]=='O')||(i+1==s.length())){
				c++;
				continue;
			}
			int temp=0;
			int j=i+1;
			while((s[j]>='0')&&(s[j]<='9')){
				temp*=10;
				temp+=s[j]-'0';
				j++;
			}
			c+=temp;
		}else if(s[i]=='O'){
			if((s[i+1]=='C')||(s[i+1]=='H')||(s[i+1]=='O')||(i+1==s.length())){
				o++;
				continue;
			}
			int temp=0;
			int j=i+1;
			while((s[j]>='0')&&(s[j]<='9')){
				temp*=10;
				temp+=s[j]-'0';
				j++;
			}
			o+=temp;
		}else if(s[i]=='H'){
			if((s[i+1]=='C')||(s[i+1]=='H')||(s[i+1]=='O')||(i+1==s.length())){
				h++;
				continue;
			}
			int temp=0;
			int j=i+1;
			while((s[j]>='0')&&(s[j]<='9')){
				temp*=10;
				temp+=s[j]-'0';
				j++;
			}
			h+=temp;
		}
	}
	//cout<<"C"<<c<<"H"<<h<<"O"<<o<<endl;
	if(h%2==1){
		c*=2;
		o*=2;
		h*=2;
	}
	int no2=c*2+h/2;
	while((no2-o)%2==1){
		c*=2;
		o*=2;
		h*=2;
		no2=c*2+h/2;
	}
	cout<<c<<" "<<h/2;
	return 0;
}
