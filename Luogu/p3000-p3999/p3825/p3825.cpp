#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 3;
const int INF = 1e9;
int n, m, d;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], low[N], cnt;
int sta[N], tt;
int scc[N], sc;
bool vis[N];
void tarjan(int p)
{
	dfn[p] = low[p] = ++cnt;
	sta[++tt] = p;
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(!dfn[j])
		{
			tarjan(j);
			low[p] = min(low[p], low[j]);
		}
		else if(vis[j])
		{
			low[p] = min(low[p], dfn[j]);
		}
	}
	if(dfn[p] == low[p])
	{
		sc++;
		while(sta[tt] != p)
		{
			scc[sta[tt]] = sc;
			vis[sta[tt]] = false;
			tt--;
		}
		scc[sta[tt]] = sc;
		vis[sta[tt]] = false;
		tt--;
	}
}
void init()
{
	for(int i = 1; i <= 2 * n; i++)
	{
		h[i] = -1;
		dfn[i] = low[i] = 0;
		vis[i] = false;
		scc[i] = 0;
	}
	tt = 0;
	sc = 0;
	cnt = 0;
	idx = 0;
}
char s[N], col[N];
struct Resc
{
	int a, b;
	char x, y;
};
Resc q[N];
int to[N];
int neg(int x) { return x > n ? x - n : x + n; }
int id(int x, char c)
{
	if(s[x] == 'A')return c == 'B' ? x : neg(x);
	if(s[x] == 'B')return c == 'C' ? x : neg(x);
	if(s[x] == 'C')return c == 'A' ? x : neg(x);
}
int main()
{
	scanf("%d%d", &n, &d);
	scanf("%s", col + 1);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		string x, y;
		cin >> a >> x >> b >> y;
		q[i] = { a,b,x[0],y[0] };
	}
	d = 0;
	for(int i = 1; i <= n; i++)
		if(col[i] == 'x')
			to[++d] = i;
	for(int S = 0; S < (1 << d); S++)
	{
		init();
		for(int i = 1; i <= n; i++)
			s[i] = col[i] - 'a' + 'A';
		for(int i = 1; i <= d; i++)
			s[to[i]] = 'A' + ((S >> (i - 1)) & 1);
		for(int i = 1; i <= m; i++)
		{
			if(q[i].x == s[q[i].a])continue;
			else if(q[i].y == s[q[i].b])add(id(q[i].a, q[i].x), neg(id(q[i].a, q[i].x)));
			else add(id(q[i].a, q[i].x), id(q[i].b, q[i].y)), add(neg(id(q[i].b, q[i].y)), neg(id(q[i].a, q[i].x)));
		}
		for(int i = 1; i <= n * 2; i++)
			if(!dfn[i])tarjan(i);
		bool flag = true;
		for(int i = 1; i <= n; i++)
		{
			if(scc[i] == scc[i + n])
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			for(int i = 1; i <= n; i++)
			{
				if(scc[i] < scc[i + n])
				{
					if(s[i] == 'A')putchar('B');
					else if(s[i] == 'B')putchar('C');
					else putchar('A');
				}
				else
				{
					if(s[i] == 'A')putchar('C');
					else if(s[i] == 'B')putchar('A');
					else putchar('B');
				}
			}
			putchar('\n');
			return 0;
		}
	}
	puts("-1");
	return 0;
}
