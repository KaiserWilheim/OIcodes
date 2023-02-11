#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n, m, q;
int val[N];
int u[N], v[N], w[N];
vector<pair<int, int>>e[N];
void add(int a, int b, int c)
{
	e[a].emplace_back(b, c);
	e[b].emplace_back(a, c);
}
mt19937_64 rnd(time(0) ^ 19260817);
int dep[N];
void dfs1(int p, int fa)
{
	dep[p] = dep[fa] + 1;
	for(auto i : e[p])
	{
		int v = i.first, id = i.second;
		if(v == fa)continue;
		if(dep[v])w[id] = rnd();
		else dfs1(v, p);
	}
}
void dfs2(int p, int fa)
{
	for(auto i : e[p])
	{
		int v = i.first, id = i.second;
		if(w[id] || v == fa)continue;
		dfs2(v, p);
		val[p] ^= val[v];
		w[id] = val[v];
	}
}
int a[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u[i], &v[i]);
		add(u[i], v[i], i);
	}
	dfs1(1, 0);
	for(int i = 1; i <= m; i++)
		val[u[i]] ^= w[i], val[v[i]] ^= w[i];
	dfs2(1, 0);
	scanf("%d", &q);
	while(q--)
	{
		int c;
		scanf("%d", &c);
		for(int i = 1; i <= c; i++)
			scanf("%d", &a[i]);
		bool flag = true;
		for(int i = 1; i < (1 << c); i++)
		{
			int val = 0;
			for(int j = 1; j <= c; j++)
				if((i >> (j - 1)) & 1)val ^= w[a[j]];
			if(!val)flag = false;
		}
		if(flag)puts("Connected");
		else puts("Disconnected");
	}
	return 0;
}
