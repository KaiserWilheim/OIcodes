#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int a[N];
ll s[N], s1[N], s2[N];
ll tmp[N], tot;
struct BIT
{
	#define lowbit(i) ((i)&-(i))
	ll minn[N], maxn[N];
	void clear()
	{
		for(int i = 1; i <= tot; i++)
			minn[i] = 1e10, maxn[i] = -1e10;
	}
	void addmin(int x, ll c)
	{
		for(int i = x; i <= tot; i += lowbit(i))
			minn[i] = min(minn[i], c);
	}
	void addmax(int x, ll c)
	{
		for(int i = x; i <= tot; i += lowbit(i))
			maxn[i] = max(maxn[i], c);
	}
	ll segmin(int x)
	{
		ll res = 1e10;
		for(int i = x; i; i -= lowbit(i))
			res = min(res, minn[i]);
		return res;
	}
	ll segmax(int x)
	{
		ll res = -1e10;
		for(int i = x; i; i -= lowbit(i))
			res = max(res, maxn[i]);
		return res;
	}
};
BIT bit;
bool chq(ll mid)
{
	s[0] = 0;
	tot = 0;
	for(int i = 1; i <= n; i++)
	{
		s[i] = s[i - 1] + a[i];
		tmp[++tot] = s[i - 1];
		tmp[++tot] = s[i] - mid;
	}
	sort(tmp + 1, tmp + 1 + tot);
	tot = unique(tmp + 1, tmp + 1 + tot) - tmp - 1;
	for(int i = 1; i <= n; i++)
	{
		s1[i] = lower_bound(tmp + 1, tmp + 1 + tot, s[i - 1]) - tmp;
		s2[i] = lower_bound(tmp + 1, tmp + 1 + tot, s[i] - mid) - tmp;
	}
	ll res1 = 0, res2 = 0;
	bit.clear();
	bit.addmax(tot - s1[1] + 1, 0);
	bit.addmin(tot - s1[1] + 1, 0);
	for(int i = 1; i <= n; i++)
	{
		res1 = bit.segmin(tot - s2[i] + 1);
		res2 = bit.segmax(tot - s2[i] + 1);
		if(i != n)bit.addmax(tot - s1[i + 1] + 1, res2 + 1);
		if(i != n)bit.addmin(tot - s1[i + 1] + 1, res1 + 1);
	}
	res1++, res2++;
	if(res1 <= m && m <= res2)return true;
	else return false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	ll l = -1e10, r = 1e10;
	while(l < r)
	{
		ll mid = (l + r) >> 1;
		if(chq(mid))r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}