#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
int kpd(int a, int b)
{
	return b ? kpd(b, a % b) : a;
}
int n, m;
int P, Q;
ll t;
int a[N], b[N];
int vis[N], pos[N];
ll dis[N], cyc[N], sum[N], len;
ll prf(ll a, ll x)
{
	if(!x)return 0;
	ll b = (a + (x - 1) * P) % Q;
	if(x + dis[a] > len)return sum[a] - (cyc[a] - cyc[b] - pos[a]);
	else return cyc[b] - cyc[a] + pos[a];
}
ll calc(ll T)
{
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(T < a[i])continue;
		ll st = (T - a[i]) / P + 1;
		ans += st / len * sum[a[i]] + prf(a[i], st % len);
	}
	return ans;
}
int main()
{
	scanf("%d%d%d%d%lld", &P, &Q, &n, &m, &t);
	if(P > Q)
	{
		swap(P, Q), swap(n, m);
		for(int i = 1; i <= m; i++)
			scanf("%d", &b[i]);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
	}
	else
	{
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++)
			scanf("%d", &b[i]);
	}
	for(int i = 1; i <= m; i++)
		pos[b[i]] = 1;
	for(int i = 0; i < Q; i++)
	{
		if(vis[i])continue;
		int p = i, k = (i + P) % Q;
		while(!vis[p])
		{
			vis[p] = true, dis[k] = dis[p] + 1;
			cyc[k] = cyc[p] + pos[k];
			p = k, k = (k + P) % Q;
		}
		k = (i + P) % Q, sum[i] = cyc[i], cyc[i] = dis[i] = 0;
		while(k != i)sum[k] = sum[i], k = (k + P) % Q;
	}
	len = Q / kpd(P, Q);
	printf("%lld\n", calc(t - 1));
	return 0;
}
