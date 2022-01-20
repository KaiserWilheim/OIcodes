#include <bits/stdc++.h>
using namespace std;
int num[10000],ans[20],qst[2][20];
int n,len=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>qst[1][i]>>qst[2][i];
	}
	/*for(int i=1;i<=n;i++){
		cout<<qst[1][i]<<qst[2][i];
	}*/
	for(int i=1;i<=n;i++){
		memset(num,0,10000);
		num[1]=1;
		len=1;
		for(int j=2;j<=qst[1][i];j++){
			for(int k=1;k<=len;k++){
				num[k]*=j;
			}
			for(int k=1;k<=len;k++){
				if(num[k]>=10){
					num[k+1]+=(num[k]-num[k]%10)/10;
					num[k]=num[k]%10;
					if(k==len)len++;
				}
			}
			/*for(int k=1;k<=len;k++){
				cout<<num[k];
			}
			cout<<endl;*/
		}
		for(int j=1;j<=len;j++){
			if(num[j]==qst[2][i])ans[i]++;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
