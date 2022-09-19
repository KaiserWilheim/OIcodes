#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
#define lowbit(x) (x&(-x))
int n;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int a[N], o[N];
int tr[N];
void segadd(int x)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i]++;
}
int segsum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int ans[N];
void dfs(int p, int fa)
{
	ans[p] = -(segsum(n) - segsum(a[p]));
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
	}
	ans[p] += segsum(n) - segsum(a[p]);
	segadd(a[p]);
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		o[i] = a[i];
	}
	sort(o + 1, o + 1 + n);
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(o + 1, o + 1 + n, a[i]) - o;
	for(int i = 2; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		add(i, x), add(x, i);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}