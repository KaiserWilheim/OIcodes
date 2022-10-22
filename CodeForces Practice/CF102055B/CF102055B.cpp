#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int lm[N], dk[N];
bool vis[N], col[N];
vector<int>vec;
struct Node
{
	int l, r, ld, rd;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		return lhs.l < rhs.l;
	}
};
void dfs(int p, int fa)
{
	vec.push_back(p);
	col[p] = !col[fa];
	vis[p] = true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])continue;
		dfs(e[i], p);
	}
}
Node a[N];
int cnt;
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		h[i] = -1;
		vis[i] = col[i] = false;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &lm[i], &dk[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		if(vis[i])continue;
		vec.clear();
		dfs(i, 0);
		int maxl = 0, minl = INT_MAX;
		int maxd = 0, mind = INT_MAX;
		for(int k : vec)
		{
			for(int j = h[k]; ~j; j = ne[j])
			{
				if(col[k] == col[e[j]])
				{
					puts("IMPOSSIBLE");
					return;
				}
			}
			if(col[k])
			{
				maxd = max(maxd, lm[k]);
				mind = min(mind, lm[k]);
				maxl = max(maxl, dk[k]);
				minl = min(minl, dk[k]);
			}
			else
			{
				maxl = max(maxl, lm[k]);
				minl = min(minl, lm[k]);
				maxd = max(maxd, dk[k]);
				mind = min(mind, dk[k]);
			}
		}
		if(maxl > maxd)swap(minl, mind), swap(maxl, maxd);
		cnt++;
		a[cnt] = { minl,maxl,mind,maxd };
	}
	sort(a + 1, a + 1 + cnt);
	multiset<int>s1;
	multiset<int, greater<int>>s2;
	int ans = INT_MAX;
	for(int i = 1; i <= cnt; i++)
	{
		s1.insert(a[i].l);
		s2.insert(a[i].r);
	}
	ans = *s2.begin() - *s1.begin();
	for(int i = 1; i <= cnt; i++)
	{
		auto it1 = s1.find(a[i].l);
		s1.erase(it1);
		auto it2 = s2.find(a[i].r);
		s2.erase(it2);
		s1.insert(a[i].ld);
		s2.insert(a[i].rd);
		ans = min(ans, *s2.begin() - *s1.begin());
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
	{
		idx = cnt = 0;
		printf("Case %d: ", i);
		solve();
	}
	return 0;
}