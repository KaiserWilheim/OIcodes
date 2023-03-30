#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(i) (i&-i)
const int N = 5010, M = 100010;
int n, m;
int op[M], dir[M], x[M], y[M], r[M];
int ans[M];
struct BIT1
{
	int c[N * 2];
	void clear() { memset(c, 0, sizeof(c)); }
	void add(int x, int y, int k)
	{
		x = max(x, 1), y = min(y, 2 * n);
		for(int i = x; i <= 2 * n; i += lowbit(i))
			c[i] += k;
		for(int i = y + 1; i <= 2 * n; i += lowbit(i))
			c[i] -= k;
	}
	int sum(int x)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			res += c[i];
		return res;
	}
};
struct BIT2
{
	int c[N * 2][N];
	void clear() { memset(c, 0, sizeof(c)); }
	void add(int l, int r, int x, int y, int k)
	{
		l = max(l, 1), r = min(r, 2 * n);
		for(int i = l; i <= 2 * n; i += lowbit(i))
			for(int j = x; j <= n; j += lowbit(j))
				c[i][j] += k;
		for(int i = r + 1; i <= 2 * n; i += lowbit(i))
			for(int j = x; j <= n; j += lowbit(j))
				c[i][j] -= k;
		for(int i = l; i <= 2 * n; i += lowbit(i))
			for(int j = y + 1; j <= n; j += lowbit(j))
				c[i][j] -= k;
		for(int i = r + 1; i <= 2 * n; i += lowbit(i))
			for(int j = y + 1; j <= n; j += lowbit(j))
				c[i][j] += k;
	}
	int sum(int x, int y)
	{
		int res = 0;
		for(int i = x; i; i -= lowbit(i))
			for(int j = y; j; j -= lowbit(j))
				res += c[i][j];
		return res;
	}
};
BIT1 bit;
BIT2 bit1, bit2;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &op[i]);
		if(op[i] == 2)scanf("%d%d", &x[i], &y[i]);
		else scanf("%d%d%d%d", &dir[i], &x[i], &y[i], &r[i]);
	}
	bit.clear(), bit1.clear(), bit2.clear();
	for(int i = 1; i <= m; i++)
	{
		if(op[i] == 1)
		{
			if(dir[i] == 1)
			{
				bit.add(x[i] + y[i], x[i] + y[i] + r[i], 1);
				bit1.add(x[i] + y[i], x[i] + y[i] + r[i], 1, x[i] - 1, 1);
				bit2.add(x[i] + y[i], x[i] + y[i] + r[i], 1, y[i] - 1, 1);
			}
			else if(dir[i] == 4)
			{
				bit.add(x[i] + y[i] - r[i], x[i] + y[i], 1);
				bit1.add(x[i] + y[i] - r[i], x[i] + y[i], x[i] + 1, n, 1);
				bit2.add(x[i] + y[i] - r[i], x[i] + y[i], y[i] + 1, n, 1);
			}
		}
		else
		{
			ans[i] += bit.sum(x[i] + y[i]) - bit1.sum(x[i] + y[i], x[i]) - bit2.sum(x[i] + y[i], y[i]);
		}
	}
	bit.clear(), bit1.clear(), bit2.clear();
	for(int i = 1; i <= m; i++)
	{
		if(op[i] == 1)
		{
			if(dir[i] == 2)
			{
				bit.add(x[i] + n + 1 - y[i], x[i] + n + 1 - y[i] + r[i], 1);
				bit1.add(x[i] + n + 1 - y[i], x[i] + n + 1 - y[i] + r[i], 1, x[i] - 1, 1);
				bit2.add(x[i] + n + 1 - y[i], x[i] + n + 1 - y[i] + r[i], y[i] + 1, n, 1);
			}
			else if(dir[i] == 3)
			{
				bit.add(x[i] + n + 1 - y[i] - r[i], x[i] + n + 1 - y[i], 1);
				bit1.add(x[i] + n + 1 - y[i] - r[i], x[i] + n + 1 - y[i], x[i] + 1, n, 1);
				bit2.add(x[i] + n + 1 - y[i] - r[i], x[i] + n + 1 - y[i], 1, y[i] - 1, 1);
			}
		}
		else
		{
			ans[i] += bit.sum(x[i] + n + 1 - y[i]) - bit1.sum(x[i] + n + 1 - y[i], x[i]) - bit2.sum(x[i] + n + 1 - y[i], y[i]);
		}
	}
	for(int i = 1; i <= m; i++)
		if(op[i] == 2)printf("%d\n", ans[i]);
	return 0;
}
