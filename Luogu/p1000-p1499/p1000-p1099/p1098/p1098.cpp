#include <bits/stdc++.h>
using namespace std;
int main(){
	string inp;
	int p1,p2,p3;
	cin>>p1>>p2>>p3;
	cin>>inp;
	for(int i=0;i<inp.size();i++){
		if((inp[i]=='-')&&(inp[i-1]<inp[i+1])){
			if(!i){
				cout<<inp[i];
				continue;
			}
			if((inp[i+1]-inp[i-1]>=27)||(inp[i-1]=='-')||(inp[i+1]=='-')){
				cout<<inp[i];
				continue;
			}
			if(inp[i+1]-inp[i-1]==1)continue;
			/*if(inp[i+1]-inp[i-1]==2){
				if(p1==1){
					char m=inp[i-1]+1;
					cout<<m;
				}else if((p1==2)&&(inp[i-1]>='a')){
					char m=inp[i-1]+1-'a'+'A';
					cout<<m;
				}else if(p1==3){
					for(int j=1;j<=p2;j++){
						cout<<"*";
					}
				}
				continue;
			}*/
			if(p1==1){
				if(p3==1){
					for(char j=inp[i-1]+1;j<inp[i+1];j++){
						for(int l=1;l<=p2;l++){
							cout<<j;
						}
					}
				}else{
					for(char j=inp[i+1]-1;j>inp[i-1];j--){
						for(int l=1;l<=p2;l++){
							cout<<j;
						}
					}
				}
			}else if(p1==2){
				if(inp[i-1]>='a'){
					if(p3==1){
						for(char j=inp[i-1]+1;j<inp[i+1];j++){
							for(int l=1;l<=p2;l++){
								char m=j-('a'-'A');
								cout<<m;
							}
						}
					}else{
						for(char j=inp[i+1]-1;j>inp[i-1];j--){
							for(int l=1;l<=p2;l++){
								char m=j-('a'-'A');
								cout<<m;
							}
						}
					}
				}else{
					if(p3==1){
						for(char j=inp[i-1]+1;j<inp[i+1];j++){
							for(int l=1;l<=p2;l++){
								cout<<j;
							}
						}
					}else{
						for(char j=inp[i+1]-1;j>inp[i-1];j--){
							for(int l=1;l<=p2;l++){
								cout<<j;
							}
						}
					}
				}
				
			}else if(p1==3){
				int n=inp[i+1]-inp[i-1]-1;
				n*=p2;
				for(int j=1;j<=n;j++){
					cout<<"*";
				}
			}
			continue;
		}
		cout<<inp[i];
	}
	return 0;
}
