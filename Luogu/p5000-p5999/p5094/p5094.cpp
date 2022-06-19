#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int n;
struct cow
{
	int v, x;
	bool operator < (const cow &a)const
	{
		return v < a.v;
	}
}a[N];
int s[N], c[N];
int tsum = 0;
int maxn = 0;
int lowbit(int a)
{
	return a & -a;
}
void add(int tr[], int x, int c)
{
	for(int i = x; i <= maxn; i += lowbit(i))
		tr[i] += c;
}
int sum(int tr[], int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		int v, x;
		scanf("%lld%lld", &v, &x);
		a[i] = { v,x };
		maxn = max(maxn, x);
	}
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int lsum = sum(s, a[i].x);
		int lcnt = sum(c, a[i].x);
		ans += a[i].v * (((a[i].x * lcnt) - lsum) + (tsum - lsum - (a[i].x * (i - 1 - lcnt))));
		add(s, a[i].x, a[i].x);
		add(c, a[i].x, 1);
		tsum += a[i].x;
	}
	printf("%lld\n", ans);
	return 0;
}
