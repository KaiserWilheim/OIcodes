#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000010;
int n, m;
struct Trie
{
	int c[N][2];
	ll maxn[N];
	int tot = 1;
	void insert(int x, ll v)
	{
		int p = 1;
		maxn[p] = max(maxn[p], v);
		for(int i = 30; ~i; i--)
		{
			int k = (x >> i & 1);
			if(!c[p][k])c[p][k] = ++tot;
			p = c[p][k];
			maxn[p] = max(maxn[p], v);
		}
	}
	ll query(int x)
	{
		int p = 1;
		ll res = -1e18;
		for(int i = 30; ~i; i--)
		{
			int k = (x >> i & 1);
			if(m >> i & 1)
			{
				res = max(res, maxn[c[p][k]]);
				p = c[p][k ^ 1];
			}
			else p = c[p][k];
		}
		return max(res, maxn[p]);
	}
	Trie()
	{
		memset(c, 0, sizeof(c));
		memset(maxn, 0xc1, sizeof(maxn));
	}
};
Trie tr;
ll c[N], b[N];
ll ans;
void dfs1(int i, int w, ll v)
{
	if(i == n / 2 + 1)
	{
		if(w <= m)ans = max(ans, v);
		tr.insert(w, v);
		return;
	}
	dfs1(i + 1, w, v);
	dfs1(i + 1, w ^ c[i], v + b[i]);
}
void dfs2(int i, int w, ll v)
{
	if(i == n + 1)
	{
		if(w <= m)ans = max(ans, v);
		ans = max(tr.query(w) + v, ans);
		return;
	}
	dfs2(i + 1, w, v);
	dfs2(i + 1, w ^ c[i], v + b[i]);
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)cin >> c[i];
	for(int i = 1; i <= n; i++)cin >> b[i];
	dfs1(1, 0, 0);
	dfs2(n / 2 + 1, 0, 0);
	cout << ans << endl;
	return 0;
}