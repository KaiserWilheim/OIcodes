#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N * 14;
const ll mod = 1e9 + 7;
int n, m;
ll f[N];
int vis[N];
int h[N], e[M], ne[M], idx = 1;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			add(j, i);
	f[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		for(int k = h[i - 1]; k; k = ne[k])
		{
			int j = e[k];
			if(vis[j] == i || j >= i)continue;
			vis[j] = i;
			f[i] = (f[i] + f[j]) % mod;
		}
		for(int k = h[i]; k; k = ne[k])
		{
			int j = e[k];
			if(vis[j] == i || j >= i)continue;
			vis[j] = i;
			f[i] = (f[i] + f[j]) % mod;
		}
		for(int k = h[i + 1]; k; k = ne[k])
		{
			int j = e[k];
			if(vis[j] == i || j >= i)continue;
			vis[j] = i;
			f[i] = (f[i] + f[j]) % mod;
		}
	}
	ll ans = 0;
	for(int i = 1; i < n; i++)
		ans = (ans + f[i]) % mod;
	printf("%lld\n", ans * n % mod);
	return 0;
}