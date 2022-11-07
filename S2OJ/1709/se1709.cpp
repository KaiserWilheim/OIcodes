#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int read()
{
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	while(isdigit(c))x = (x * 10) + (c ^ 48), c = getchar();
	return x;
}
int n, m;
int a[N];
int be[N];
struct Query
{
	int l, r, k, id;
	bool operator < (const Query &rhs)const
	{
		if(be[l] == be[rhs.l])
			return (be[l] ^ 1) ? (r > rhs.r) : (r < rhs.r);
		return l < rhs.l;
	}
};
Query q[N];
int ans[N];
int cnt[N], lans[N];
int main()
{
	n = read();
	int S = sqrt(n);
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i <= n; i++)
		be[i] = (i - 1) / S;
	m = read();
	for(int i = 1; i <= m; i++)
	{
		int l, r, k;
		l = read(), r = read(), k = read();
		q[i] = { l,r,k,i };
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	lans[0] = n;
	for(int i = 1; i <= m; i++)
	{
		while(l > q[i].l)
		{
			l--;
			cnt[a[l]]++;
			lans[cnt[a[l]]]++;
		}
		while(r < q[i].r)
		{
			r++;
			cnt[a[r]]++;
			lans[cnt[a[r]]]++;
		}
		while(l < q[i].l)
		{
			lans[cnt[a[l]]]--;
			cnt[a[l]]--;
			l++;
		}
		while(r > q[i].r)
		{
			lans[cnt[a[r]]]--;
			cnt[a[r]]--;
			r--;
		}
		ans[q[i].id] = lans[q[i].k];
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}