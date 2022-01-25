#include<bits/stdc++.h>
using namespace std;
const int N = 100010, M = N << 1;
int n;
struct TrieTree
{
	int s[2];
	int occ;
}tr[N * 32];
int tot = 1;
int w[M], h[N], e[M], ne[M], idx;
int dis[N];
int ans;
void add(int a, int b, int v)
{
	e[idx] = b;
	w[idx] = v;
	ne[idx] = h[a];
	h[a] = idx++;
	return;
}
void insert(int x)
{
	for(int i = 30, p = 1; i >= 0; i--)
	{
		int c = ((x >> i) & 1);
		if(!tr[p].s[c])tr[p].s[c] = ++tot;
		p = tr[p].s[c];
	}
	return;
}
void get(int x)
{
	int res = 0;
	for(int i = 30, p = 1; i >= 0; i--)
	{
		int c = ((x >> i) & 1);
		if(tr[p].s[c ^ 1])
		{
			p = tr[p].s[c ^ 1];
			res |= (1 << i);
		}
		else
		{
			p = tr[p].s[c];
		}
	}
	ans = max(ans, res);
	return;
}
void dfs(int p, int fa)
{
	insert(dis[p]);
	get(dis[p]);
	for(int i = h[p]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa)continue;
		dis[v] = dis[p] ^ w[i];
		dfs(v, p);
	}
	return;
}
int main()
{
	cin >> n;
	memset(h, -1, sizeof(h));
	for(int i = 1; i < n; i++)
	{
		int a, b, v;
		scanf("%d%d%d", &a, &b, &v);
		add(a, b, v);
		add(b, a, v);
	}
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
