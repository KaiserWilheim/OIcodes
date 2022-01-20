#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
char sc[62510];
int main(){
	int n=0;
	for(int i=1;i<=62500;i++){
		cin>>sc[i];
		if(sc[i]=='E'){
			break;
		}
		n++;
	}
	int h=0,e=0;
	for(int i=1;i<=n;i++){
		if(sc[i]=='W'){
			h++;
		}else if(sc[i]=='L'){
			e++;
		}else if(sc[i]=='e'){
			break;
		}
		if((h-e>=2)||(e-h>=2)){
			if((h>=11)||(e>=11)){
				cout<<h<<":"<<e<<endl;
				h=0;
				e=0;
			}
		}
	}
	cout<<h<<":"<<e<<endl;
	h=0;
	e=0;
	cout<<endl;
	for(int i=1;i<=n;i++){
		if(sc[i]=='W'){
			h++;
		}else if(sc[i]=='L'){
			e++;
		}else if(sc[i]=='e'){
			break;
		}
		if((h-e>=2)||(e-h>=2)){
			if((h>=21)||(e>=21)){
				cout<<h<<":"<<e<<endl;
				h=0;
				e=0;
			}
		}
	}
	cout<<h<<":"<<e<<endl;
	return 0;
}

