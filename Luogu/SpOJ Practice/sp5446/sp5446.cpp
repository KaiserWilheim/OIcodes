#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 2000010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
unordered_set<int>s[N];
struct LTable
{
	int l, r;
}p[N << 2];
int w[N], q[N], d[N];
void push(int x)
{
	p[x].r = p[N + w[x]].r;
	p[p[x].r].l = x;
	p[x].l = N + w[x];
	p[p[x].l].r = x;
}
void pop(int x)
{
	p[p[x].r].l = p[x].l;
	p[p[x].l].r = p[x].r;
}
int sta[N], tt;
void solve()
{
	for(int i = 1; i <= n; i++)
	{
		h[i] = -1;
		s[i].clear();
		p[i] = p[i + N] = { 0,0 };
		w[i] = d[i] = q[i] = 0;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
		s[v].insert(u);
		s[u].insert(v);
	}
	for(int i = 1; i <= n; i++)push(i);
	int now = 0, ans = 0;
	for(int k = n; k; k--, now++)
	{
		while(!p[N + now].r)now--;
		int x = p[N + now].r;
		pop(x);
		q[k] = x, d[x] = k;
		for(int i = h[x]; ~i; i = ne[i])
		{
			if(!d[e[i]])
			{
				pop(e[i]);
				++w[e[i]];
				push(e[i]);
			}
		}
	}
	bool flag = true;
	for(int i = 1; i <= n; i++)
	{
		tt = 0;
		for(int j = h[i]; ~j; j = ne[j])
		{
			if(d[i] < d[e[j]])
			{
				sta[++tt] = e[j];
				if(d[e[j]] < d[sta[1]])swap(sta[1], sta[tt]);
			}
		}
		for(int j = 2; j <= tt; j++)
		{
			if(!s[sta[1]].count(sta[j]))
			{
				flag = false;
				break;
			}
		}
	}
	if(!flag)puts("Imperfect");
	else puts("Perfect");
}
int main()
{
	scanf("%d%d", &n, &m);
	while(n != 0 && m != 0)
	{
		solve();
		scanf("%d%d", &n, &m);
	}
	return 0;
}
