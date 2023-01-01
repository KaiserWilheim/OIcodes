#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1;
const int INF = 1e9;
int n;
int S, T;
int h[N], e[M], f[M], ne[N], idx;
int w[N];
int d[N], pre[N], incf[N];
bool st[N];
void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}
bool spfa()
{
	memset(d, 0x3f, sizeof d);
	memset(incf, 0, sizeof incf);
	queue<int>q;
	q.push(S);
	d[S] = 0, incf[S] = INF;
	while(!q.empty())
	{
		int t = q.front();
		q.pop();
		st[t] = false;
		for(int i = h[t]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[i] && d[v] > d[t] + w[i])
			{
				d[v] = d[t] + w[i];
				pre[v] = i;
				incf[v] = min(f[i], incf[t]);
				if(!st[v])
				{
					q.push(v);
					st[v] = true;
				}
			}
		}
	}
	return incf[T] > 0;
}
void EK(int &flow, int &cost)
{
	flow = cost = 0;
	while(spfa())
	{
		int t = incf[T];
		flow += t, cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
int x[N], y[N];
map<int, int>dic;
set<pair<int, int>>s;
int tot;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		if(!dic.count(x[i]))dic[x[i]] = ++tot;
		if(!dic.count(y[i]))dic[y[i]] = ++tot;
		x[i] = dic[x[i]], y[i] = dic[y[i]];
		s.insert(make_pair(x[i], y[i]));
	}
	S = 0, T = tot * 2 + 1;
	map<int, int>cntx, cnty;
	for(int i = 1; i <= n; i++)
		cntx[x[i]]++, cnty[y[i]]++;
	for(int i = 1; i <= tot; i++)
	{
		if(!cntx.count(i))continue;
		add(S, i, cntx[i], 0);
	}
	for(int i = 1; i <= tot; i++)
	{
		if(!cnty.count(i))continue;
		add(i + tot, T, cnty[i], 0);
	}
	for(int i = 1; i <= tot; i++)
	{
		if(!cntx.count(i))continue;
		for(int j = 1; j <= tot; j++)
		{
			if(!cnty.count(j))continue;
			if(s.count(make_pair(i, j)))add(i, j + tot, 1, 1);
			else add(i, j + tot, 1, 0);
		}
	}
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", cost);
	return 0;
}