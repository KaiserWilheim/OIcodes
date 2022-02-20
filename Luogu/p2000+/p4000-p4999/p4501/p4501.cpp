#include <bits/stdc++.h>
const long long N = 200010, INF = 0x3f3f3f3f3f3f3f3f;
struct Data
{
	int p;
	long long l;
	bool operator <(const Data &?)const
	{
		return p < ?.p;
	}
}a[N];
int n, m, K;
long long dis[N];
namespace ST
{
	long long st1[N][18], st2[N][18];
	void init()
	{
		std::sort(a + 1, a + K + 1);
		for(int i = 1; i <= K; i++)
		{
			st1[i][0] = a[i].l - dis[a[i].p];
			st2[i][0] = a[i].l + dis[a[i].p];
		}
		for(int j = 1; j <= 17; j++)
		{
			for(int i = 1; i <= K - (1 << j) + 1; i++)
			{
				st1[i][j] = std::min(st1[i][j - 1], st1[i + (1 << (j - 1))][j - 1]);
				st2[i][j] = std::min(st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	int findl(int x)
	{
		Data ?; ?.p = x;
		return std::lower_bound(a + 1, a + K + 1, ?) - a;
	}
	int findr(int x)
	{
		Data ?; ?.p = x;
		return std::upper_bound(a + 1, a + K + 1, ?) - a - 1;
	}
	long long query1(int l, int r)
	{
		if(l > r) std::swap(l, r);
		l = std::max(1, l), r = std::min(r, n);
		l = findl(l), r = findr(r);
		if(l > r)return INF;
		int lim = log2(r - l + 1);
		return std::min(st1[l][lim], st1[r - (1 << lim) + 1][lim]);
	}
	long long query2(int l, int r)
	{
		if(l > r) std::swap(l, r);
		l = std::max(1, l), r = std::min(r, n);
		l = findl(l), r = findr(r);
		if(l > r)return INF;
		int lim = log2(r - l + 1);
		return std::min(st2[l][lim], st2[r - (1 << lim) + 1][lim]);
	}
}
bool checkl(int p, int x)
{
	if(x == p)return true;
	long long qwq1 = ST::query1(2 * x - p + 1, x) + dis[x];
	long long qwq2 = ST::query2(x, p - 1) - dis[x];
	long long mst = ST::query2(p, p) - dis[x];
	if(qwq1 <= mst || qwq2 <= mst)return false;
	if(2 * x - p >= 1) return ST::query1(2 * x - p, 2 * x - p) + dis[x] > mst;
	return true;
}
bool checkr(int p, int x)
{
	if(x == p)return true;
	long long qwq1 = ST::query1(p + 1, x) + dis[x];
	long long qwq2 = ST::query2(x, 2 * x - p - 1) - dis[x];
	long long mst = ST::query1(p, p) + dis[x];
	if(qwq1 <= mst || qwq2 <= mst)return false;
	if(2 * x - p <= n) return ST::query2(2 * x - p, 2 * x - p) - dis[x] >= mst;
	return true;
}
int solvel(int p)
{
	int l = 1, r = p, ans = p;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(checkl(p, mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	return ans;
}
int solver(int p)
{
	int l = p, r = n, ans = p;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if(checkr(p, mid))l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	return ans;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; i++)
	{
		scanf("%lld", &dis[i]);
		dis[i] += dis[i - 1];
	}
	while(m--)
	{
		scanf("%d", &K);
		for(int i = 1; i <= K; i++)
			scanf("%d%lld", &a[i].p, &a[i].l);
		ST::init();
		long long ans = 0;
		for(int i = 1; i <= K; i++)
		{
			ans += 1ll * (solver(a[i].p) - solvel(a[i].p) + 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
