#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010, M = N << 1;
int n, m;
int sgn(int x)
{
	if(x < 0)return -1;
	if(x > 0)return 1;
	return 0;
}
ll calc(ll a, ll b)
{
	if(a % b)return a / b + 1;
	return a / b;
}
int a[N], idx;
ll w[N], sum[N];
ll maxn[M], dp[M], rs[M];
ll get(int l, int r)
{
	l = (l - 1) % n + 1;
	r = (r - 1) % n + 1;
	if(l > r)swap(l, r);
	return sum[r] - sum[l - 1];
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	w[++idx] = a[1];
	for(int i = 2; i <= n; i++)
	{
		if(sgn(w[idx]) != sgn(a[i]))w[++idx] = a[i];
		else w[idx] += a[i];
	}
	n = idx;
	for(int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + w[i];
	for(int i = 1; i <= n; i++)
	{
		dp[i] = dp[i + n] = 1e18;
		rs[i] = rs[i + n] = -1e18;
		maxn[i] = maxn[i + n] = -1e18;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++)
		{
			maxn[i] = max(maxn[i], sum[j] - sum[i - 1]);
			maxn[j + n] = max(maxn[j + n], sum[j] - sum[i - 1]);
		}
	}
	dp[1] = 0, rs[1] = 0;
	queue<int>q;
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 1; i <= n * 2; i++)
		{
			if(!(u <= n && i >= u + n) && !(i <= n && u >= i + n))continue;
			ll d = dp[u], w = rs[u];
			if(w + get(i, u) < 0)
			{
				if(maxn[u] <= 0)continue;
				ll k = calc(-w - get(i, u), maxn[u]);
				if(k & 1)k++;
				d += k;
				w += k * maxn[u];
			}
			w += get(i, u);
			d++;
			if(d < dp[i] || (d == dp[i] && w > rs[i]))
			{
				dp[i] = d, rs[i] = w;
				q.push(i);
			}
		}
	}
	ll res = 0;
	for(int i = 1; i <= 2 * n; i++)
	{
		if(dp[i] > m)continue;
		res = max(res, rs[i]);
		ll ans = rs[i] + (m - dp[i]) * maxn[i];
		res = max(res, ans);
	}
	printf("%lld\n", res);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = 0;
		solve();
	}
	return 0;
}