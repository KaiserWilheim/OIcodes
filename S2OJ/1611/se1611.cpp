#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500010;
int n, k;
int a[N];
int pos[N];
struct node
{
	int l, r;
};
node p[N];
int sta[N], tt;
int ne[N], ls[N];
signed main()
{
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	if(k > n)
	{
		puts("0");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		pos[a[i]] = i;
		p[i] = { 0,n + 1 };
		ls[i] = 0, ne[i] = n + 1;
	}
	for(int i = 1; i <= n; i++)
	{
		while(tt && a[sta[tt]] < a[i])tt--;
		ls[i] = sta[tt];
		sta[++tt] = i;
	}
	tt = 0;
	for(int i = n; i >= 1; i--)
	{
		while(tt && a[sta[tt]] < a[i])tt--;
		if(tt)ne[i] = sta[tt];
		sta[++tt] = i;
	}
	for(int i = n; i >= n - k + 2; i--)
	{
		int x = pos[i];
		p[ls[x]].r = x, p[ne[x]].l = x;
		p[x] = { ls[x],ne[x] };
	}
	int ans = 0;
	for(int i = n - k + 1; i >= 1; i--)
	{
		int x = pos[i];
		p[ls[x]].r = x, p[ne[x]].l = x;
		p[x] = { ls[x],ne[x] };
		int lst = x, nxt = x, cnt = 0;
		while(nxt != n + 1 && cnt < k)
			nxt = p[nxt].r, cnt++;
		while(cnt < k)
			lst = p[lst].l, cnt++;
		while(nxt > x && lst)
		{
			ans += (nxt - p[nxt].l) * (lst - p[lst].l) * i;
			nxt = p[nxt].l, lst = p[lst].l;
		}
	}
	printf("%lld\n", ans);
	return 0;
}