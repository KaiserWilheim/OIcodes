#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
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
int ans[N];
int cnt[N], now;
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
	int k;
	scanf("%d%d", &n, &m);
	scanf("%d", &k);
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
		ans[q[i].id] = now;
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
