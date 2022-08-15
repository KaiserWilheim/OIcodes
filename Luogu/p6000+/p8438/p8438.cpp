#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N = 40;
int n, m, k;
int a[N];
int f[(1 << 15)], g[(1 << 15)];
signed main()
{
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	int len = (n >> 1);
	f[0] = g[0] = 0;
	for(int i = 1; i < (1ull << len); i++)
	{
		for(int j = 0; j < len; j++)
		{
			if((i >> j) & 1)
			{
				f[i] = f[i ^ (1ull << j)] ^ a[j];
				break;
			}
		}
	}
	int res = n - len;
	for(int i = 1; i <= (1ull << res); i++)
	{
		for(int j = 0; j < res; j++)
		{
			if((i >> j) & 1)
			{
				g[i] = g[i ^ (1ull << j)] ^ a[j + len];
				break;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < (1ull << len); i++)
	{
		for(int j = 0; j < (1ull << res); j++)
		{
			ans ^= (f[i] ^ g[j]) * (j * (1ull << len) + i);
		}
	}
	cout << ans << endl;
	return 0;
}
