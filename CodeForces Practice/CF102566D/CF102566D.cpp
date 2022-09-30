#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 40, M = 1000010;
int n, m;
struct Node
{
	int minn = 1e9;
	unordered_map<int, int>c;
};
Node tr[M];
int tot;
int lim[N];
int a[N][N], b[N][N];
void insert(vector<int>x, int w)
{
	int u = 0;
	for(int i = 0; i < m; i++)
	{
		if(tr[u].c.count(x[i]))u = tr[u].c[x[i]];
		else u = tr[u].c[x[i]] = ++tot;
	}
	tr[u].minn = min(tr[u].minn, w);
}
int query(vector<int>x)
{
	int u = 0;
	for(int i = 0; i < m; i++)
	{
		if(tr[u].c.count(lim[i] - x[i]))u = tr[u].c[lim[i] - x[i]];
		else return 1e9;
	}
	return tr[u].minn;
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++)
		scanf("%d", &lim[i]);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			scanf("%d%d", &a[i][j], &b[i][j]);
	int t = n / 2;
	for(int S = 0; S < (1 << t); S++)
	{
		vector<int>res(m, 0);
		for(int i = 0; i < t; i++)
		{
			if(S & (1 << i))
				for(int k = 0; k < m; k++)res[k] += b[i][k];
			else
				for(int k = 0; k < m; k++)res[k] += a[i][k];
		}
		bool flag = true;
		for(int i = 0; i < m; i++)
			if(res[i] > lim[i])flag = false;
		if(flag)insert(res, __builtin_popcount(S));
	}
	t = n - t;
	int ans = 114514;
	for(int S = 0; S < (1 << t); S++)
	{
		vector<int>res(m, 0);
		for(int i = 0; i < t; i++)
		{
			if(S & (1 << i))
				for(int k = 0; k < m; k++)res[k] += b[n - t + i][k];
			else
				for(int k = 0; k < m; k++)res[k] += a[n - t + i][k];
		}
		bool flag = true;
		for(int i = 0; i < m; i++)
			if(res[i] > lim[i])flag = false;
		if(flag)ans = min(ans, query(res) + __builtin_popcount(S));
	}
	if(ans == 114514)puts("impossible");
	else printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		for(int i = 0; i <= tot; i++)
		{
			tr[i].minn = 1e9;
			tr[i].c.clear();
		}
		tot = 0;
		solve();
	}
	return 0;
}