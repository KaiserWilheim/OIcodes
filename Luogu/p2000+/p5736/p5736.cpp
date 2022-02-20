#include <bits/stdc++.h>
using namespace std;
bool visit[100010];
int ans[110];
int main(){
	visit[0]=visit[1]=true;
	for(int i=2;i<=100000;i++){
		if(!visit[i]){
			if(100000<i*i)break;//埃氏筛只需要剔除根号n以内的素数的倍数 
			for(int j=i*i;j<=100000;j+=i)visit[j]=true;//标记 
		}
	}
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(!visit[a]){
			ans[0]++;
			ans[ans[0]]=a;
		}
	}
	for(int i=1;i<=ans[0];i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
