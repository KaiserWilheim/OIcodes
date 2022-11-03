#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, k;
set<int>g[N];
set<int>leaf[N];
struct cmp
{
	bool operator () (const int lhs, const int rhs)const
	{
		return (leaf[lhs].size() == leaf[rhs].size()) ? (lhs < rhs) : (leaf[lhs].size() > leaf[rhs].size());
	}
};
void solve()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		g[i].clear(), leaf[i].clear();
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].insert(v);
		g[v].insert(u);
	}
	if(k == 1)
	{
		printf("%d\n", n - 1);
		return;
	}
	for(int i = 1; i <= n; i++)
	{
		if(g[i].size() == 1)
			leaf[*g[i].begin()].insert(i);
	}
	set<int, cmp>s;
	for(int i = 1; i <= n; i++)
		s.insert(i);
	int ans = 0;
	while(true)
	{
		int u = *s.begin();
		if(leaf[u].size() < k)break;
		ans++;
		for(int i = 1; i <= k; i++)
		{
			int v = *leaf[u].begin();
			g[u].erase(v);
			g[v].erase(u);
			s.erase(u);
			s.erase(v);
			leaf[u].erase(v);
			if(leaf[v].count(u))leaf[v].erase(u);
			if(g[u].size() == 1)
			{
				int w = *g[u].begin();
				s.erase(w);
				leaf[w].insert(u);
				s.insert(w);
			}
			s.insert(u);
			s.insert(v);
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}