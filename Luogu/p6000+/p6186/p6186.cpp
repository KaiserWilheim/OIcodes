#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
#define ll long long
int n, m;
int a[N], b[N], d[N];
ll c[N], ans;
inline int lowbit(int x)
{
	return x & (-x);
}
inline void add(int x, ll val)
{
	while(x <= n)
	{
		c[x] += val;
		x += lowbit(x);
	}
}
inline ll sum(int x)
{
	ll res = 0;
	while(x > 0)
	{
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
int main()
{
	int tmp = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		b[i] = i - 1 - sum(a[i]);
		ans += b[i], ++d[b[i]];
		add(a[i], 1);
	}
	memset(c, 0, sizeof(c));
	add(1, ans);
	for(int i = 0; i < n; ++i)
	{
		tmp += d[i];
		add(i + 2, -(n - tmp));
	}
	for(int i = 1; i <= m; ++i)
	{
		int op, x;
		scanf("%d%d", &op, &x);
		x = min(x, n - 1);
		if(op == 1)
		{
			if(a[x] < a[x + 1])
			{
				swap(a[x], a[x + 1]);
				swap(b[x], b[x + 1]);
				add(1, 1);
				add(b[x + 1] + 2, -1);
				b[x + 1]++;
			}
			else
			{
				swap(a[x], a[x + 1]);
				swap(b[x], b[x + 1]);
				add(1, -1);
				b[x]--;
				add(b[x] + 2, 1);
			}
		}
		else printf("%lld\n", sum(x + 1));
	}
	return 0;
}
