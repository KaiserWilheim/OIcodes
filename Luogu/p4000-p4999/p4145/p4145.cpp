#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
#define lowbit(x) (x&(-x))
int n, m, k;
ll tr[N];
void segadd(int x, ll c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
ll a[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		segadd(i, a[i]);
		p[i] = i;
	}
	p[n + 1] = n + 1;
	scanf("%d", &m);
	while(m--)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(l > r)swap(l, r);
		if(op == 0)
		{
			for(int i = l; i <= r;)
			{
				segadd(i, floor(sqrt(a[i])) - a[i]);
				a[i] = floor(sqrt(a[i]));
				if(a[i] <= 1)p[i] = i + 1;
				if(i == find(i))i++;
				else i = p[i];
			}
		}
		else
		{
			printf("%lld\n", segsum(r) - segsum(l - 1));
		}
	}
	return 0;
}