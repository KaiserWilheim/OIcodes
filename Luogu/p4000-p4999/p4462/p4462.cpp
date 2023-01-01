#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = N << 1;
int n, m, k;
int a[N], sum[N];
int bl[N];
struct Node
{
	int l, r, id;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		if(bl[lhs.l] != bl[rhs.l])return lhs.l < rhs.l;
		if(bl[lhs.l] & 1)return lhs.r < rhs.r;
		else return lhs.r > rhs.r;
	}
};
Node q[N];
int cnt[M];
int ans, res[N];
void add(int x)
{
	ans += cnt[a[x] ^ k];
	cnt[a[x]]++;
}
void del(int x)
{
	cnt[a[x]]--;
	ans -= cnt[a[x] ^ k];
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int S = sqrt(n) + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] ^= a[i - 1];
		bl[i] = ((i - 1) / S) + 1;
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].l--, q[i].id = i;
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
		while(l > q[i].l)add(--l);
		while(r < q[i].r)add(++r);
		while(l < q[i].l)del(l++);
		while(r > q[i].r)del(r--);
		res[q[i].id] = ans;
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", res[i]);
	return 0;
}
