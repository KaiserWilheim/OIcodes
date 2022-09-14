#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int mdis[N], col[N];
void dfs(int p, int d, int c)
{
	if(!col[p])col[p] = c;
	if(!d || mdis[p] >= d)return;
	mdis[p] = d;
	for(int i = h[p]; ~i; i = ne[i])
		dfs(e[i], d - 1, c);
}
struct query
{
	int x, d, c;
};
query qry[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
		scanf("%d%d%d", &qry[i].x, &qry[i].d, &qry[i].c);
	for(int i = q; i >= 1; i--)
		dfs(qry[i].x, qry[i].d, qry[i].c);
	for(int i = 1; i <= n; i++)
		printf("%d\n", col[i]);
	return 0;
}