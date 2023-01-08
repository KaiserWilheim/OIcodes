#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010, M = 40010;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
struct Point
{
	int x, y;
};
Point a[N];
int dis(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}
int col[N];
bool dfs(int p, int lim)
{
	for(int q = 1; q <= n; q++)
	{
		if(p == q || dis(a[p], a[q]) <= lim)continue;
		if(col[q] == -1)
		{
			col[q] = col[p] ^ 1;
			if(!dfs(q, lim))return false;
		}
		else if(col[p] == col[q])return false;
	}
	return true;
}
int ans, sc;
bool chq(int lim)
{
	int cnt = 0;
	for(int i = 1; i <= n; i++)col[i] = -1;
	for(int i = 1; i <= n; i++)
	{
		if(col[i] == -1)
		{
			cnt++;
			col[i] = 0;
			if(!dfs(i, lim))return false;
		}
	}
	ans = lim, sc = cnt;
	return true;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	int l = 0, r = 10000;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(chq(mid))r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n%lld\n", ans, qpow(2, sc));
	return 0;
}
