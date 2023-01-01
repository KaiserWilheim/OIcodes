#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) ((x)&-(x))
const int N = 400010, M = N << 1;
int n, m;
int a[N];
int f[N];
int ans;
struct Bit1
{
	int tr[N];
	void segadd(int x, int c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr[i] += c;
	}
	int segsum(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
	int sum(int l, int r)
	{
		return segsum(r) - segsum(l - 1);
	}
};
struct Bit2
{
	int tr1[N], tr2[N];
	void segadd(int x, int y, int c)
	{
		for(int i = x; i <= n; i += lowbit(i))
			tr1[i] += c, tr2[i] += c * x;
		for(int i = y + 1; i <= n; i += lowbit(i))
			tr1[i] -= c, tr2[i] -= c * (y + 1);
	}
	int sum(int l, int r)
	{
		int res = 0;
		for(int i = r; i; i -= lowbit(i))
			res += tr1[i] * (r + 1) - tr2[i];
		for(int i = l - 1; i; i -= lowbit(i))
			res -= tr1[i] * l - tr2[i];
		return res;
	}
};
Bit1 bit1;
Bit2 bit2;
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		bit1.segadd(a[i], 1);
		f[i] = bit1.sum(1, a[i] - 1);
		bit2.segadd(a[i], a[i], f[i]);
	}
	for(int i = n + 1; i <= 2 * n; i++)
	{
		bit2.segadd(a[i - n] + 1, n, -1);
		int tmp = bit2.sum(a[i - n], a[i - n]);
		bit2.segadd(a[i - n], a[i - n], -tmp);
		bit1.segadd(a[i - n], -1);
		f[i] = bit1.sum(1, a[i - n] - 1);
		ans += bit2.sum(1, a[i - n] - 1);
		bit2.segadd(a[i - n], a[i - n], f[i]);
		bit1.segadd(a[i - n], 1);
	}
	printf("%lld\n", ans);
	return 0;
}