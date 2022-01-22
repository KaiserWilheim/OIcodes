#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
bool num[30];
int main(){
	//freopen("power.in","r",stdin);
	//freopen("power.out","w",stdout);
	int n;
	scanf("%d",&n);
	if(n%2==1){
		cout<<"-1"<<endl;
		return 0;
	}else{
		for(int i=1;i<=25;i++){
			n=n>>1;
			if(n%2==1){
				num[i]=true;
			}
		}
	}
	for(int i=29;i>1;i--){
		if(num[i]==true){
			int m=1<<i;
			cout<<m<<" ";
		}
	}
	if(num[1]==true){
		cout<<"2";
	}
	return 0;
}
