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
	now -= (cnt[x] > 1);
	cnt[x]++;
	now += (cnt[x] > 1);
}
void del(int x)
{
	now -= (cnt[x] > 1);
	cnt[x]--;
	now += (cnt[x] > 1);
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
		ans[q[i].id] = (now == 0);
	}
	for(int i = 1; i <= m; i++)
		puts(ans[i] ? "Yes" : "No");
	return 0;
}
