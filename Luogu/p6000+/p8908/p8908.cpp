#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 15010;
#define lowbit(i) (i&-i)
struct BIT
{
	int n;
	int cnt[N];
	ll sum[N];
	void clear()
	{
		for(int i = 1; i <= n; i++)
			cnt[i] = 0, sum[i] = 0;
	}
	void segadd(int c, int k)
	{
		for(int i = k; i <= n; i += lowbit(i))
			cnt[i] += c, sum[i] += 1ll * c * k;
	}
	int segcnt(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += cnt[i];
		return res;
	}
	ll segsum(int x)
	{
		ll res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += sum[i];
		return res;
	}
};
BIT bit;
int n;
char s[N];
int a[N];
int cnt0[N], cnt1[N];
int pos[N], cntp;
ll cnt, sum;
ll ans;
void work(int l, int r, int ql, int qr, bool flag)
{
	r -= l, qr -= ql;
	for(int x = 0; x <= r + qr; x++)
	{
		if(!flag || (x + l + ql) % 2 == 0)
		{
			int lx = max(0, x - qr), rx = min(x, r);
			int c = rx - lx + 1;
			bit.segadd(c, x + l + ql);
			cnt += c, sum += 1ll * c * (x + l + ql);
		}
	}
}
void solve(int l, int r)
{
	bool flag = (r - l + 1) & 1;
	sum = 0, cnt = 0;
	bit.clear();
	while(l <= r)
	{
		work(pos[l - 1] + 1, pos[l], pos[r], pos[r + 1] - 1, flag);
		int x = pos[l] + pos[r];
		ll val = sum - 2 * bit.segsum(x) + 1ll * x * (2 * bit.segcnt(x) - cnt);
		if(l == r)ans += val / 2;
		else ans += val;
		l++, r--;
	}
}
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		a[i] = (s[i] == 'H');
	for(int i = 1; i <= n; i++)
	{
		cnt0[i] = cnt0[i - 1] + (a[i] == 0);
		cnt1[i] = cnt1[i - 1] + (a[i] == 1);
	}
	for(int i = 1; i <= n; i++)
		if(a[i])pos[++cntp] = i;
	pos[cntp + 1] = n + 1;
	bit.n = n * 2;
	for(int i = 1; i <= cntp; i++)solve(1, i);
	for(int i = 2; i <= cntp; i++)solve(i, cntp);
	for(int l = 1; l <= n; l++)
	{
		for(int r = l + 1; r <= n; r++)
		{
			int x = cnt0[r] - cnt0[l - 1], y = cnt1[r] - cnt1[l - 1];
			if((x & 1) && (y & 1))ans--;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
