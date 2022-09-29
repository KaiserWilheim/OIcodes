#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
const ll bs1 = 19260817, bs2 = 19491001;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * a);
		a = (a * a);
		x >>= 1;
	}
	return res;
}
int n, m;
ll h[N][N];
ll h1[N][N], h2[N][N];
ll qpow1[N], qpow2[N];
ll get(int x, int y, int k)
{
	ll res = h[x][y];
	res = res - h[x][y - k] * qpow1[k] - h[x - k][y] * qpow2[k];
	res = res + h[x - k][y - k] * qpow1[k] * qpow2[k];
	return res;
}
ll get1(int x, int y, int k)
{
	ll res = h1[x][y - k + 1];
	res = res - h1[x][y + 1] * qpow1[k] - h1[x - k][y - k + 1] * qpow2[k];
	res = res + h1[x - k][y + 1] * qpow1[k] * qpow2[k];
	return res;
}
ll get2(int x, int y, int k)
{
	ll res = h2[x - k + 1][y];
	res = res - h2[x - k + 1][y - k] * qpow1[k] - h2[x + 1][y] * qpow2[k];
	res = res + h2[x + 1][y - k] * qpow1[k] * qpow2[k];
	return res;
}
int main()
{
	qpow1[0] = qpow2[0] = 1;
	for(int i = 1; i <= 1000; i++)
	{
		qpow1[i] = qpow1[i - 1] * bs1;
		qpow2[i] = qpow2[i - 1] * bs2;
	}
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &h[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			h1[i][j] = h2[i][j] = h[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			h[i][j] = h[i][j - 1] * bs1 + h[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = m; j >= 1; j--)
			h1[i][j] = h1[i][j + 1] * bs1 + h1[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			h2[i][j] = h2[i][j - 1] * bs1 + h2[i][j];
	for(int j = 1; j <= m; j++)
		for(int i = 1; i <= n; i++)
			h[i][j] = h[i - 1][j] * bs2 + h[i][j];
	for(int j = 1; j <= m; j++)
		for(int i = 1; i <= n; i++)
			h1[i][j] = h1[i - 1][j] * bs2 + h1[i][j];
	for(int j = 1; j <= m; j++)
		for(int i = n; i >= 1; i--)
			h2[i][j] = h2[i + 1][j] * bs2 + h2[i][j];
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int l = 0, r = min(min(i, j), min(n - i, m - j)) + 1;
			int sum = 0;
			while(l < r)
			{
				int mid = (l + r) >> 1;
				ll a = get(i + mid, j + mid, mid + mid);
				ll b = get1(i + mid, j + mid, mid + mid);
				ll c = get2(i + mid, j + mid, mid + mid);
				if(a == b && b == c && a == c)sum = mid, l = mid + 1;
				else r = mid;
			}
			ans += sum;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int l = 0, r = min(min(i, j), min(n - i, m - j)) + 1;
			int sum = 0;
			while(l < r)
			{
				int mid = (l + r) >> 1;
				ll a = get(i + mid, j + mid, mid + mid + 1);
				ll b = get1(i + mid, j + mid, mid + mid + 1);
				ll c = get2(i + mid, j + mid, mid + mid + 1);
				if(a == b && b == c && a == c)sum = mid, l = mid + 1;
				else r = mid;
			}
			ans += sum;
		}
	}
	ans += n * m;
	printf("%d\n", ans);
	return 0;
}