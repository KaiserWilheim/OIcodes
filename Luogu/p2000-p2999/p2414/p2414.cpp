#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = N << 1;
int read()
{
	int x = 0, flag = 1; char c;
	while((c = getchar()) < '0' || c > '9') if(c == '-') flag = -1;
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * flag;
}
int n, m;
char s[N];
int len;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[++idx] = b, ne[idx] = h[a], h[a] = idx;
}

int a[N];
int dfn[N], out[N], indx;

struct AC
{
	int s[26];
	int v, fail, fa;
}tr[N];
int cnt;
void insert()
{
	len = strlen(s);
	for(int i = 0, now = 0; i < len; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			if(!tr[now].s[s[i] - 'a'])
			{
				tr[now].s[s[i] - 'a'] = ++cnt;
				tr[cnt].fa = now;
			}
			now = tr[now].s[s[i] - 'a'];
		}
		if(s[i] == 'P')
			a[++n] = now;
		if(s[i] == 'B')
			now = tr[now].fa;
	}
}
void build_fail()
{
	queue<int>q;
	for(int i = 0; i < 26; i++)
		if(tr[0].s[i])q.push(tr[0].s[i]);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
		{
			if(tr[u].s[i])
			{
				tr[tr[u].s[i]].fail = tr[tr[u].fail].s[i];
				q.push(tr[u].s[i]);
			}
			else
			{
				tr[u].s[i] = tr[tr[u].fail].s[i];
			}
		}
	}
}

void dfs(int u, int p)
{
	dfn[u] = ++indx;
	for(int i = h[u]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v ^ p)dfs(v, u);
	}
	out[u] = indx;
}

int lowbit(int x)
{
	return x & -x;
}
int c[N];
void segadd(int x, int v)
{
	for(int i = x; i <= indx; i += lowbit(i))
		c[i] += v;
}
int segsum(int x)
{
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += c[i];
	return ans;
}

struct query
{
	int x, id;
};
vector<query>g[N];

int ans[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%s", s);
	insert();
	build_fail();
	for(int i = 1; i <= cnt; i++)
		add(i, tr[i].fail), add(tr[i].fail, i);
	dfs(0, 0);
	m = read();
	for(int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		g[y].push_back({ x,i });
	}
	for(int i = 0, now = 0, j = 0; i < len; i++)
	{
		if(s[i] == 'P')
		{
			j++;
			for(int k = 0; k < g[j].size(); k++)
			{
				int x = g[j][k].x, id = g[j][k].id;
				ans[id] = segsum(out[a[x]]) - segsum(dfn[a[x]] - 1);
			}
		}
		if(s[i] == 'B')
		{
			segadd(dfn[now], -1);
			now = tr[now].fa;
		}
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			now = tr[now].s[s[i] - 'a'];
			segadd(dfn[now], 1);
		}
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
