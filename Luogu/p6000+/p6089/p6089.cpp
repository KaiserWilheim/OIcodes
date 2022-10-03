#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
const int N = 500010;
#define lowbit(x) (x&(-x))
int n, m;
ld tr[N];
void segadd(int x, ld c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
ld segsum(int x)
{
	ld res = 0.0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
ld qpow(ld a, int x)
{
	ld res = 1.0;
	while(x)
	{
		if(x & 1)res *= a;
		a *= a;
		x >>= 1;
	}
	return res;
}
vector<int>e[N];
int main()
{
	scanf("%d%d", &n, &m);
	ld p;
	scanf("%Lf", &p);
	ld ans = 0;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}
	for(int u = 1; u <= n; u++)
	{
		if(e[u].empty())continue;
		sort(e[u].begin(), e[u].end());
		ld now = p / (1 - qpow(1 - p, e[u].size()));
		for(int v : e[u])
		{
			ans += segsum(n - v) * now;
			now *= (1 - p);
		}
		now = p / (1 - qpow(1 - p, e[u].size()));
		for(int v : e[u])
		{
			segadd(n - v + 1, now);
			now *= (1 - p);
		}
	}
	printf("%.2Lf", ans);
	return 0;
}