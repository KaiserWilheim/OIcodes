#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(i) (i&-i)
const int N = 200010, M = 5;
const int V = 2e5 + 1;
int n, m;
int a[M][N];
ll c[N << 1];
void segadd(int x)
{
	for(int i = x; i <= 2 * V; i += lowbit(i))
		c[i]++;
}
ll segsum(int x)
{
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += c[i];
	return res;
}
struct Node
{
	int op, x, y, w;
	bool operator < (const Node &rhs)const
	{
		if(x != rhs.x)return x < rhs.x;
		return op < rhs.op;
	}
};
Node q[N << 1];
int idx;
ll calc(int x, int y, int z)
{
	ll res = 0;
	memset(c, 0, sizeof(c));
	idx = 0;
	for(int i = 1; i <= n; i++)
	{
		q[++idx] = { 0,a[x][i] - a[y][i] + (x > y),a[y][i] - a[z][i] + (y > z),0 };
		q[++idx] = { 1,a[y][i] - a[x][i],a[z][i] - a[y][i],a[y][i] };
	}
	sort(q + 1, q + 1 + idx);
	for(int i = 1; i <= idx; i++)
	{
		if(q[i].op == 0)segadd(q[i].y + V);
		else res += q[i].w * segsum(q[i].y + V);
	}
	return res;
}
ll ans;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for(int i = m + 1; i <= 4; i++)
		for(int j = 1; j <= n; j++)
			a[i][j] = a[i - m][j];
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= n; j++)
			ans += 2ll * n * a[i][j];
	for(int i = 1; i <= 4; i++)
		for(int j = 1; j <= 4; j++)
			for(int k = 1; k <= 4; k++)
				if(i != j && j != k && i != k)
					ans -= calc(i, j, k);
	printf("%lld\n", ans);
	return 0;
}
