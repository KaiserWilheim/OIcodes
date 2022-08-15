#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
struct dsu
{
	int p[N];
	int find(int x)
	{
		if (p[x] != x)p[x] = find(p[x]);
		return p[x];
	}
}L, R;
int n, m;
#define lowbit(x) (x&-x)
ll tr[N];
void add(int x, ll c)
{
	for (int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
ll sum(int x)
{
	ll res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
ll ans;
vector<pair<int, int> >st[N];
vector<int>h[N];
int main()
{
	scanf("%d", &n);
	L.p[n + 1] = R.p[n + 1] = n + 1;
	for (int i = 1; i <= n; i++)
	{
		L.p[i] = R.p[i] = i;
		int x;
		scanf("%d", &x);
		h[x].push_back(i);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		st[y].push_back(make_pair(x, c));
	}
	for (int i = 1; i <= n; i++)
	{
		for (pair<int, int> s : st[i])
		{
			ll S = sum(s.first);
			if (S > s.second)ans += s.second;
			else
			{
				ans += S;
				add(L.find(s.first) + 1, s.second - S);
				add(R.find(s.first), S - s.second);
			}
		}
		for (int j : h[i])
		{
			L.p[j] = j - 1;
			R.p[j] = j + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}