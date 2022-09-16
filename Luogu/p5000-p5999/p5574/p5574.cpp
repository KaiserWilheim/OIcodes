#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 50100;
#define lowbit(x) (x&-x)
int n, k;
int a[N];
int p[27][N];
ll f[27][N];
ll c[N];
void segadd(int x)
{
	for(int i = x; i <= n; i += lowbit(i))
		c[i]++;
}
void segdel(int x)
{
	for(int i = x; i <= n; i += lowbit(i))
		c[i]--;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += c[i];
	return res;
}
int dl = 1, dr = 0;
ll ans;
ll query(int l, int r)
{
	while(l < dl)
	{
		ans += dr - dl + 1;
		ans -= segsum(a[--dl]);
		segadd(a[dl]);
	}
	while(dr < r)
	{
		ans += segsum(a[++dr]);
		segadd(a[dr]);
	}
	while(dl < l)
	{
		segdel(a[dl]);
		ans += segsum(a[dl++]);
		ans -= dr - dl + 1;
	}
	while(r < dr)
	{
		segdel(a[dr]);
		ans -= segsum(a[dr--]);
	}
	return ans;
}
void solve(int x, int l, int r, int tl, int tr)
{
	int mid = (l + r) >> 1;
	int pos;
	ll res;
	f[x][mid] = (1ll << 60);
	for(int i = tl; i <= min(tr, mid - 1); i++)
	{
		res = f[x - 1][i] + query(i + 1, mid);
		if(res < f[x][mid])
		{
			f[x][mid] = res;
			pos = i;
		}
	}
	p[x][mid] = pos;
	if(l < mid)solve(x, l, mid - 1, tl, pos);
	if(mid < r)solve(x, mid + 1, r, pos, tr);
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		f[1][i] = f[1][i - 1] + segsum(a[i]);
		segadd(a[i]);
	}
	memset(c, 0, sizeof(c));
	for(int i = 2; i <= k; i++)
		solve(i, i, n, i - 1, n);
	printf("%lld\n", f[k][n]);
	return 0;
}