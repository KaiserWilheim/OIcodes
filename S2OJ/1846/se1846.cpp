#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, M = N << 1;
int n, m;
struct AC
{
	int s[26];
	int fail;
	int sum;
};
AC tr[N];
char s[N];
int cnt = 1, len;
int pos[N];
void insert(int id)
{
	int p = 1;
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - 'a';
		if(!tr[p].s[c])tr[p].s[c] = ++cnt;
		p = tr[p].s[c];
	}
	pos[id] = p;
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 26; i++)
	{
		if(!tr[1].s[i])tr[1].s[i] = 1;
		else tr[tr[1].s[i]].fail = 1, q.push(tr[1].s[i]);
	}
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
		{
			if(!tr[p].s[i])tr[p].s[i] = tr[tr[p].fail].s[i];
			else tr[tr[p].s[i]].fail = tr[tr[p].fail].s[i], q.push(tr[p].s[i]);
		}
	}
}
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int fa[N], son[N], dep[N], sz[N], top[N];
int dfn[N], tot;
void dfs1(int p, int fa)
{
	::fa[p] = fa, dep[p] = dep[fa] + 1, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
		if(sz[e[i]] > sz[son[p]])son[p] = e[i];
	}
}
void dfs2(int p, int t)
{
	top[p] = t, dfn[p] = ++tot;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p] || e[i] == son[p])continue;
		dfs2(e[i], e[i]);
	}
}
int lca(int p, int q)
{
	while(top[p] != top[q])
	{
		if(dep[top[p]] < dep[top[q]])swap(p, q);
		p = fa[top[p]];
	}
	if(dep[p] < dep[q])swap(p, q);
	return q;
}
struct BIT
{
#define lowbit(i) (i&-i)
	int tr[N];
	void segadd(int x, int c)
	{
		for(int i = x; i <= cnt; i += lowbit(i))
			tr[i] += c;
	}
	int segsum(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
};
BIT bit;
int sta[N];
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
signed main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		insert(i);
	}
	get_fail();
	for(int i = 2; i <= cnt; i++)
		add(tr[i].fail, i), add(i, tr[i].fail);
	dfs1(1, 0);
	dfs2(1, 1);
	scanf("%d", &m);
	while(m--)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			scanf("%s", s + 1);
			len = strlen(s + 1);
			int p = 1;
			for(int i = 1; i <= len; i++)
			{
				int c = s[i] - 'a';
				p = tr[p].s[c];
				sta[i] = p;
			}
			sort(sta + 1, sta + 1 + len, cmp);
			for(int i = 1; i <= len; i++)
				bit.segadd(dfn[sta[i]], 1);
			for(int i = 1; i < len; i++)
				bit.segadd(dfn[lca(sta[i], sta[i + 1])], -1);
		}
		else
		{
			int x;
			scanf("%d", &x);
			int p = pos[x];
			int res = bit.segsum(dfn[p] + sz[p] - 1) - bit.segsum(dfn[p] - 1);
			printf("%d\n", res);
		}
	}
	return 0;
}
