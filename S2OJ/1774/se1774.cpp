#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int n;
struct Edge
{
	int u, v, w;
};
Edge edge[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
void soyuz(int a, int b)
{
	int fa = find(a), fb = find(b);
	if(fa != fb)p[fa] = fb;
}
set<int>s[N];
int pos[N], cnt[N];
bool vis[N], stadt[N];
int ans[N];
int tot;
void loeschn(int p)
{
	if(cnt[p])cnt[p]--;
	if(cnt[p])return;
	if(s[p].size() <= 2)
	{
		if(!stadt[p])tot--;
		if(s[p].size() == 1)
		{
			int u = *s[p].begin();
			s[u].erase(p);
			if(s[u].size() <= 2 && !stadt[u])loeschn(u);
		}
		if(s[p].size() == 2)
		{
			int u = *s[p].begin(), v = *next(s[p].begin());
			s[u].insert(v), s[v].insert(u);
			s[u].erase(p), s[v].erase(p);
			if(s[u].size() <= 2 && !stadt[u])loeschn(u);
			if(s[v].size() <= 2 && !stadt[v])loeschn(v);
		}
		stadt[p] = false;
	}
	else
	{
		stadt[p] = false;
		tot++;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		p[i] = i;
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = { u,v,w };
		if(w == 0)soyuz(u, v);
	}
	for(int i = 1; i < n; i++)
	{
		int u = find(edge[i].u), v = find(edge[i].v);
		if(u == v)continue;
		s[u].insert(v), s[v].insert(u);
	}
	for(int i = 1; i <= n; i++)
	{
		cnt[find(i)]++;
		stadt[i] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &pos[i]);
		pos[i] = p[pos[i]];
	}
	ans[1] = 1;
	for(int i = n; i >= 2; i--)
	{
		ans[i] = (tot == 0);
		loeschn(pos[i]);
	}
	for(int i = 1; i <= n; i++)
		printf("%d", ans[i]);
	putchar('\n');
	return 0;
}