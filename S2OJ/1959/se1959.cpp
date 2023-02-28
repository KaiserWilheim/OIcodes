#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
using namespace std;
ll prime[N];
int vis[N];
void seive(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])prime[++prime[0]] = i;
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j])break;
		}
	}
}
ll n;
ll p[N], cnt[N], tt;
ll num[N], tot;
bool chq(ll k)
{
	if(k * k * k < n)return false;
	ll k1 = k >> 1, k2 = k - k1;
	if(k1 * k1 * k1 + k2 * k2 * k2 > n)return false;
	return true;
}
void dfs(int pos, ll now)
{
	if(pos == tt + 1)
	{
		if(chq(now))num[++tot] = now;
		return;
	}
	for(int i = 0; i <= cnt[pos]; i++)
	{
		dfs(pos + 1, now);
		now *= p[pos];
	}
}
int main()
{
	seive(1e6);
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld", &n);
		tt = 0, tot = 0;
		ll w = n;
		for(int i = 1; i <= prime[0]; i++)
		{
			if(prime[i] * prime[i] > n)break;
			if(n % prime[i])continue;
			p[++tt] = prime[i], cnt[tt] = 0;
			while(n % prime[i] == 0)n /= prime[i], cnt[tt]++;
		}
		if(n != 1)p[++tt] = n, cnt[tt] = 1;
		for(int i = 1; i <= tt; i++)cnt[i] <<= 1;
		n = w * w;
		dfs(1, 1);
		bool flag = false;
		for(int i = 1; i <= tot; i++)
		{
			ll now = num[i], k1 = now * now * now - n;
			if(k1 % (now * 3))continue;
			k1 /= now * 3;
			ll k2 = now * now - 4 * k1;
			if(k2 < 0)continue;
			ll k3 = k2;
			k2 = sqrt(k3);
			if(k2 * k2 != k3)continue;
			ll x = (now + k2) >> 1, y = (now - k2) >> 1;
			if(!x || !y)continue;
			flag = true;
			printf("%lld %lld\n", x, y);
			break;
		}
		if(!flag)puts("impossible");
	}
	return 0;
} 
