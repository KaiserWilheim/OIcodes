#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
struct Edge
{
	int u, v, w;
	bool operator < (const Edge &a)const
	{
		return w < a.w;
	}
};
vector<Edge>e;
int a[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		maxn = max(maxn, a[i]);
	}
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	for(int i = 1; i <= n; i++)
	{
		int k = upper_bound(a + 1, a + 1 + n, a[i]) - a;
		if(k <= n && a[k] < 2 * a[i])e.push_back({ i, k, a[k] % a[i] });
		for(int d = 2; d * a[i] <= maxn; d++)
		{
			int k = lower_bound(a + 1, a + 1 + n, d * a[i]) - a;
			if(k > n || a[k] >= (d + 1) * a[i])continue;
			e.push_back({ i, k, a[k] % a[i] });
		}
	}
	for(int i = 1; i <= n; i++)
		p[i] = i;
	m = e.size();
	sort(e.begin(), e.end());
	ll ans = 0;
	int tot = n;
	for(int i = 1; i <= m; i++)
	{
		int u = e[i - 1].u, v = e[i - 1].v, w = e[i - 1].w;
		int fa = find(u), fb = find(v);
		if(fa == fb)continue;
		tot--;
		ans += w;
		p[fb] = fa;
		if(tot == 1)break;
	}
	printf("%lld\n", ans);
	return 0;
}
