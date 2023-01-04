#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = N << 1, INF = 1e8;
int n, m;
int S, T;
int h[N], e[M], f[M], ne[M], idx;
int th[N], te[M], tf[M], tne[M];
int q[N], d[N], cur[N];
void add(int a, int b, int c)
{
	e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}
bool bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof(d));
	q[0] = S, d[S] = 0, cur[S] = h[S];
	while(hh <= tt)
	{
		int t = q[hh++];
		for(int i = h[t]; ~i; i = ne[i])
		{
			int ver = e[i];
			if(d[ver] == -1 && f[i])
			{
				d[ver] = d[t] + 1;
				cur[ver] = h[ver];
				if(ver == T)  return true;
				q[++tt] = ver;
			}
		}
	}
	return false;
}
int find(int u, int limit)
{
	if(u == T) return limit;
	int flow = 0;
	for(int i = cur[u]; ~i && flow < limit; i = ne[i])
	{
		cur[u] = i;
		int ver = e[i];
		if(d[ver] == d[u] + 1 && f[i])
		{
			int t = find(ver, min(f[i], limit - flow));
			if(!t) d[ver] = -1;
			f[i] -= t, f[i ^ 1] += t, flow += t;
		}
	}
	return flow;
}
int dinic()
{
	int r = 0, flow;
	while(bfs()) while(flow = find(S, INF)) r += flow;
	return r;
}

void init()
{
	memset(h, -1, sizeof(h));
	memset(e, 0, sizeof(e));
	memset(ne, 0, sizeof(ne));
	memset(f, 0, sizeof(f));
	memset(cur, 0, sizeof(cur));
	idx = 0;
}
void cpy(int t)
{
	if(t == 1)
	{
		memcpy(th, h, sizeof(h));
		memcpy(te, e, sizeof(e));
		memcpy(tne, ne, sizeof(ne));
		memcpy(tf, f, sizeof(f));
	}
	else if(t == 2)
	{
		memcpy(h, th, sizeof(h));
		memcpy(e, te, sizeof(e));
		memcpy(ne, tne, sizeof(ne));
		memcpy(f, tf, sizeof(f));
	}
	memset(cur, 0, sizeof(cur));
}
int main()
{
	int a1, a2, an, b1, b2, bn;
	while(scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) == 7)
	{
		init();
		a1++, a2++, b1++, b2++;
		for(int i = 1; i <= n; i++)
		{
			char s[100];
			cin >> s + 1;
			for(int j = 1; j <= i; j++)
			{
				if(s[j] == 'N')add(i, j, INF), add(j, i, INF);
				else if(s[j] == 'O')add(i, j, 1), add(j, i, 1);
			}
		}
		cpy(1);
		S = 0, T = n + 1;
		add(S, a1, an), add(S, b1, bn);
		add(a2, T, an), add(b2, T, bn);
		int fir = dinic();
		cpy(2);
		add(S, a1, an), add(S, b2, bn);
		add(a2, T, an), add(b1, T, bn);
		int sec = dinic();
		if((fir == an + bn) && (sec == an + bn))puts("Yes");
		else puts("No");
	}
	return 0;
}
