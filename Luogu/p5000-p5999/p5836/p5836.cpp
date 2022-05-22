#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
char s[N];
int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dep[N], fa[N], son[N], sz[N];
int top[N], nw[N], id[N], cnt;
int G[N], H[N];
void dfs1(int p, int father, int depth)
{
	dep[p] = depth, fa[p] = father, sz[p] = 1;
	G[p] = G[father] + (s[p] == 'G'), H[p] = H[father] + (s[p] == 'H');
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == father)continue;
		dfs1(j, p, depth + 1);
		sz[p] += sz[j];
		if(sz[son[p]] < sz[j])son[p] = j;
	}
}
void dfs2(int p, int t)
{
	top[p] = t, id[p] = ++cnt, nw[cnt] = p;
	if(!son[p])return;
	dfs2(son[p], t);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int j = e[i];
		if(j == fa[p] || j == son[p])continue;
		dfs2(j, j);
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
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	cin >> s + 1;
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	while(m--)
	{
		int a, b;
		char op[10];
		scanf("%d%d%s", &a, &b, &op);
		int c = lca(a, b);
		if(op[0] == 'H')
		{
			int res = H[a] + H[b] - 2 * H[c] + (s[c] == 'H');
			if(res == 0)printf("0");
			else printf("1");
		}
		else if(op[0] == 'G')
		{
			int res = G[a] + G[b] - 2 * G[c] + (s[c] == 'G');
			if(res == 0)printf("0");
			else printf("1");
		}
		else
		{
			cout << 'E';
		}
	}
	putchar('\n');
	return 0;
}
