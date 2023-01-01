#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 100000;
int n, m, k;
int ms;
int a[N], sum[N];
int bl[N];
struct Node
{
	int l, r, id, op, x;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		if(bl[lhs.l] != bl[rhs.l])return lhs.l < rhs.l;
		if(bl[lhs.l] & 1)return lhs.r < rhs.r;
		else return lhs.r > rhs.r;
	}
};
Node q[N];
bitset<N>now1, now2;
int cnt[N];
int ans, res[N];
void add(int x)
{
	if(cnt[a[x]]++ == 0)now1[a[x]] = 1, now2[M - a[x]] = 1;
}
void del(int x)
{
	if(--cnt[a[x]] == 0)now1[a[x]] = 0, now2[M - a[x]] = 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	int S = sqrt(n) + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		bl[i] = ((i - 1) / S) + 1;
	}
	for(int i = 1; i <= m; i++)
	{
		int op, l, r, x;
		scanf("%d%d%d%d", &op, &l, &r, &x);
		q[i] = { l,r,i,op,x };
	}
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
		while(l > q[i].l)add(--l);
		while(r < q[i].r)add(++r);
		while(l < q[i].l)del(l++);
		while(r > q[i].r)del(r--);
		int op = q[i].op, x = q[i].x;
		if(op == 1)
		{
			if((now1 & (now1 << x)).any())res[q[i].id] = 1;
		}
		else if(op == 2)
		{
			if((now1 & (now2 >> (M - x))).any())res[q[i].id] = 1;
		}
		else if(op == 3)
		{
			for(int j=1;j*j<=x;j++)
			{
				if(!(x % j))
				{
					if(now1[j] && now1[x / j])
					{
						res[q[i].id] = 1;
						break;
					}
				}
			}
		}
	}
	for(int i = 1; i <= m; i++)
	{
		if(res[i])puts("hana");
		else puts("bi");
	}
	return 0;
}
