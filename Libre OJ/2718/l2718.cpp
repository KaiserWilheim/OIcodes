#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 400010, M = N << 1;

int read()
{
	int x = 0;
	char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

int n, m;
struct EdgeInOrigin
{
	int u, v, l, a;
}nd[M], p[M];
struct EdgeWithValue
{
	int e, ne, w;
}t[M];
int h[N], idx;
void AddWithValue(int a, int b, int c)
{
	t[idx] = { b,h[a],c };
	h[a] = idx++;
}

struct Heap
{
	int u, v;
	friend bool operator < (Heap a, Heap b)
	{
		return a.v > b.v;
	}
};
bool vis[N];
int dis[N];
void dijkstra(int s)
{
	memset(vis, false, sizeof(vis));
	memset(dis, 63, sizeof(dis));
	priority_queue<Heap>q;
	dis[s] = 0;
	q.push({ s,dis[s] });
	while(!q.empty())
	{
		Heap x = q.top();
		q.pop();
		int u = x.u;
		if(vis[u])continue;
		vis[u] = true;
		for(int i = h[u]; ~i; i = t[i].ne)
		{
			int v = t[i].e;
			if(vis[v])continue;
			if(dis[v] > dis[u] + t[i].w)
			{
				dis[v] = dis[u] + t[i].w;
				q.push({ v,dis[v] });
			}
		}
	}
}

struct EdgeWithoutValue
{
	int e, ne;
}tr[M << 1];
int fr[N], indx;
void AddWithoutValue(int a, int b)
{
	tr[indx] = { b,fr[a] };
	fr[a] = indx++;
}

int dep[N], f[N][20];
int fa[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
void dfs(int u, int father)
{
	dep[u] = dep[father] + 1, f[u][0] = father;
	for(int i = 1; i <= 19; i++)f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = fr[u]; ~i; i = tr[i].ne)
	{
		int v = tr[i].e;
		dfs(v, u);
		p[u].l = min(p[u].l, p[v].l);
	}
}
bool cmp(EdgeInOrigin x, EdgeInOrigin y)
{
	return x.a > y.a;
}
void kruskal()
{
	int tot = 0, cnt = n;
	for(int i = 1; i <= (n << 1); i++)fa[i] = i;
	sort(nd + 1, nd + m + 1, cmp);
	for(int i = 1; i <= m; i++)
	{
		int u = nd[i].u, v = nd[i].v;
		int pa = find(u), pb = find(v);
		if(pa != pb)
		{
			AddWithoutValue(++cnt, pa);
			AddWithoutValue(cnt, pb);
			fa[pa] = cnt;
			fa[pb] = cnt;
			p[cnt].a = nd[i].a;
			tot++;
		}
		if(tot == n - 1)break;
	}
	dfs(cnt, 0);
}

int query(int x, int y)
{
	for(int i = 19; i >= 0; i--)
		if(dep[x] - (1 << i) > 0 && p[f[x][i]].a > y)
			x = f[x][i];
	return p[x].l;
}
int main()
{
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	int T = read();
	while(T--)
	{
		int lastans = 0;
		n = read(), m = read();
		memset(nd, 0, sizeof(nd));
		memset(h, -1, sizeof(h));
		memset(fr, -1, sizeof(fr));
		memset(f, 0, sizeof(f));
		indx = 0, idx = 0;
		for(int i = 1; i <= m; i++)
		{
			int u = read(), v = read(), l = read(), a = read();
			nd[i] = { u,v,l,a };
			AddWithValue(u, v, l);
			AddWithValue(v, u, l);
		}
		dijkstra(1);
		for(int i = 1; i <= n; i++)p[i].l = dis[i];
		for(int i = n + 1; i <= (n << 1); i++)p[i].l = 0x3f3f3f3f;
		kruskal();
		int q = read(), K = read(), S = read();
		while(q--)
		{
			int x = (K * lastans + read() - 1) % n + 1;
			int y = (K * lastans + read()) % (S + 1);
			lastans = query(x, y);
			printf("%d\n", lastans);
		}
	}
	return 0;
}
