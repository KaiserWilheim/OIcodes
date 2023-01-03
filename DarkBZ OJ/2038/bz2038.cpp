#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
ll kpd(ll a, ll b)
{
	return b ? kpd(b, a % b) : a;
}
int col[N];
int bl[N];
struct Query
{
	int l, r, id;
	friend bool operator < (const Query &lhs, const Query &rhs)
	{
		if(bl[lhs.l] != bl[rhs.l])return lhs.l < rhs.l;
		else
		{
			if(bl[lhs.l] & 1)return lhs.r < rhs.r;
			else return lhs.r > rhs.r;
		}
	}
};
Query q[N];
pair<ll, ll> ans[N];
ll cnt[N], now;
void add(int x)
{
	now -= cnt[x] * cnt[x];
	cnt[x]++;
	now += cnt[x] * cnt[x];
}
void del(int x)
{
	now -= cnt[x] * cnt[x];
	cnt[x]--;
	now += cnt[x] * cnt[x];
}
int main()
{
	scanf("%d%d", &n, &m);
	int S = sqrt(n);
	for(int i = 1; i <= n; i++)
		bl[i] = (i - 1) / S + 1;
	for(int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	for(int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		q[i] = { l,r,i };
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
		while(r < q[i].r)add(col[++r]);
		while(l > q[i].l)add(col[--l]);
		while(r > q[i].r)del(col[r--]);
		while(l < q[i].l)del(col[l++]);
		if(q[i].l == q[i].r)
		{
			ans[q[i].id] = make_pair(0, 1);
			continue;
		}
		ll a = now - (q[i].r - q[i].l + 1);
		ll b = 1ll * (q[i].r - q[i].l + 1) * (q[i].r - q[i].l);
		ll g = kpd(a, b);
		ans[q[i].id] = make_pair(a / g, b / g);
	}
	for(int i = 1; i <= m; i++)
		printf("%lld/%lld\n", ans[i].first, ans[i].second);
	return 0;
}
