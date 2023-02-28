#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = 200010, K = 6;
int n, m, k;
vector<ll>w[K];
vector<ll>sum[K];
ll f[M], g[M];
void solve(int l, int r, int dl, int dr, int k, int b)
{
	if(l > r)return;
	int x = (l + r) >> 1;
	int mid = -1;
	for(int i = dl; i <= dr; i++)
	{
		if(x >= i && x - i <= w[k].size())
		{
			if(mid == -1 || g[k * x + b] <= sum[k][x - i] + f[k * i + b])
			{
				mid = i;
				g[k * x + b] = sum[k][x - i] + f[k * i + b];
			}
		}
	}
	solve(l, x - 1, dl, mid, k, b);
	solve(x + 1, r, mid, dr, k, b);
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
	{
		ll u, v;
		scanf("%lld%lld", &u, &v);
		w[u].push_back(v);
	}
	for(int i = 1; i <= k; i++)
	{
		sort(w[i].begin(), w[i].end(), greater<ll>());
		sum[i].push_back(0);
		for(int j = 1; j <= w[i].size(); j++)
			sum[i].push_back(sum[i][j - 1] + w[i][j - 1]);
	}
	for(int i = 1; i <= k; i++)
	{
		for(int j = 0; j < i; j++)
		{
			if((m / i) * i + j <= m)solve(0, m / i, 0, m / i, i, j);
			else solve(0, m / i - 1, 0, m / i - 1, i, j);
		}
		for(int j = 0; j <= m; j++)f[j] = g[j];
	}
	for(int i = 1; i <= m; i++)
		printf("%lld\n", f[i]);
	return 0;
}
