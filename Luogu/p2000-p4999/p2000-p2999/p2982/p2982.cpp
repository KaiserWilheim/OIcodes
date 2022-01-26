#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>q[100001];
int a[100001],num[100001],ans[100001];
int lowbit(int x)
{
	return -x & x;
}
void add(int x,int k)
{
	while(x<=n)
	{
		num[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=num[x];
		x-=lowbit(x);		
	}
	return s;
}
void dfs(int u,int fa)
{
	int k=a[u];
	ans[k]=sum(k-1);
	add(k,1);
	for(int i=0;i<q[u].size();i++)
	{
		int t=q[u][i];
		if(t==fa)
		continue;
		dfs(t,u);
	}
	add(k,-1);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		q[u].push_back(v);
		q[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		int t;
		scanf("%d",&t);
		a[t]=i;
	}
	dfs(1,1);
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
