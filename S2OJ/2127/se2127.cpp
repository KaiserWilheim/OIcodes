#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
const int B = 120;
int n, q;
struct AC
{
	int s[26];
	int f;
	int fail;
};
AC tr[N];
int m;
char s[N];
int len;
int pos[N], bl[N];
void insert(int id)
{
	int p = 0;
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - 'a';
		if(!tr[p].s[c])tr[p].s[c] = ++m, tr[m].f = p;
		p = tr[p].s[c];
	}
	pos[id] = p;
}
void get_fail()
{
	queue<int>q;
	for(int c = 0; c < 26; c++)
		if(tr[0].s[c])q.push(tr[0].s[c]);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int c = 0; c < 26; c++)
		{
			if(!tr[p].s[c])tr[p].s[c] = tr[tr[p].fail].s[c];
			else tr[tr[p].s[c]].fail = tr[tr[p].fail].s[c], q.push(tr[p].s[c]);
		}
	}
}
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfn[N], sz[N], ed[N];
int tis;
void dfs1(int p, int fa)
{
	dfn[p] = ++tis, sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs1(e[i], p);
		sz[p] += sz[e[i]];
	}
	ed[p] = tis;
}
int a[N];
vector<ll>d[N];
vector<pair<int, int>>qry[N];
int qid[N], ans[N];
int c[N];
#define lowbit(i) (i&-i)
void segadd(int x, int k)
{
	for(int i = x; i <= m; i += lowbit(i))
		c[i] += k;
}
int segsum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += c[i];
	return res;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		len = strlen(s + 1);
		insert(i);
		bl[i] = len > B;
	}
	get_fail();
	for(int i = 1; i <= m; i++)
		add(i, tr[i].fail), add(tr[i].fail, i);
	tis = -1;
	dfs1(0, 0);
	for(int i = 1; i <= n; i++)
	{
		if(!bl[i])continue;
		for(int j = 1; j <= m; j++)a[j] = 0;
		for(int p = pos[i]; p; p = tr[p].f)a[dfn[p]] = 1;
		for(int j = 1; j <= m; j++)a[j] += a[j - 1];
		d[i].resize(n + 1);
		for(int j = 1; j <= n; j++)
			d[i][j] = a[ed[pos[j]]] - a[dfn[pos[j]] - 1] + d[i][j - 1];
	}
	for(int i = 1; i <= q; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		if(bl[k])ans[i] = d[k][r] - d[k][l - 1];
		else qid[i] = k, qry[l - 1].emplace_back(i, -1), qry[r].emplace_back(i, 1);
	}
	for(int i = 1; i <= n; i++)
	{
		segadd(dfn[pos[i]], 1);
		segadd(ed[pos[i]] + 1, -1);
		for(auto x : qry[i])
		{
			int y = x.first, sgn = x.second;
			for(int p = pos[qid[y]]; p; p = tr[p].f)
				ans[y] += sgn * segsum(dfn[p]);
		}
	}
	for(int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
