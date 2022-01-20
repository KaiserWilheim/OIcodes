#include <bits/stdc++.h>
using namespace std;
int ans[1000010]={0,0,1,2,2,3,3,4,4,4};
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=10;i<=m;i++){
		bool cxq=true;
		for(int j=2;j<=sqrt(i);j++){
			if(i%j==0){
				cxq=false;
				break;
			}
		}
		if(cxq==true){
			ans[i]=ans[i-1]+1;
		}else if(cxq==false){
			ans[i]=ans[i-1];
		}
	}
	/*for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}*/
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		if((r>m)||(l<1)||(l>m)||(r<1)){
			cout<<"Crossing the line"<<endl;
		}else{
			cout<<ans[r]-ans[l-1]<<endl;
		}
	}
	
	return 0;
}
