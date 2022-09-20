#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
#define lowbit(x) (x&(-x))
int n, m, k;
ll tr[N];
void segadd(int x, int c)
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
int a[N];
int d[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	for(int i = 1; i <= 1000000; i++)
		for(int j = i; j <= 1000000; j += i)
			d[j]++;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		segadd(i, a[i]);
		p[i] = i;
	}
	p[n + 1] = n + 1;
	while(m--)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			for(int i = l; i <= r;)
			{
				segadd(i, d[a[i]] - a[i]);
				a[i] = d[a[i]];
				if(a[i] <= 2)p[i] = i + 1;
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