#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m, q;
int a[N];
int cnt[N], tcol;
int lim[N];
void add(int i)
{
	cnt[i]++;
	if(cnt[i] == lim[i])tcol++;
}
void del(int i)
{
	if(cnt[i] == lim[i])tcol--;
	cnt[i]--;
}
bool chq(int len)
{
	for(int i = 0; i <= m; i++)
		cnt[i] = 0;
	tcol = 0;
	for(int i = 1; i <= len; i++)
		add(a[i]);
	if(tcol == q)return true;
	for(int i = len + 1; i <= n; i++)
	{
		add(a[i]), del(a[i - len]);
		if(tcol == q)return true;
	}
	return false;
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		cnt[a[i]]++;
	}
	int minc = 0;
	for(int i = 1; i <= q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(cnt[x] < y)
		{
			puts("impossible");
			return 0;
		}
		lim[x] = y;
		minc += y;
	}
	int l = minc, r = n;
	int mid, ans = n;
	while(l < r)
	{
		mid = (l + r) >> 1;
		if(chq(mid))r = mid, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
