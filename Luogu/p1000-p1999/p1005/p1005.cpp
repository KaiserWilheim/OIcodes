#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110, M = 30;
const int base = 10000;
struct INT
{
	int n;
	int a[M];
	INT() { n = 0, memset(a, 0, sizeof(a)); }
	INT(int x)
	{
		n = 0, memset(a, 0, sizeof(a));
		while(x)
		{
			a[++n] = x % base;
			x /= base;
		}
	}
	friend INT operator + (const INT &lhs, const INT &rhs)
	{
		INT res;
		res.n = max(lhs.n, rhs.n);
		for(int i = 1; i <= res.n; i++)
			res.a[i] = lhs.a[i] + rhs.a[i];
		for(int i = 1; i <= res.n; i++)
		{
			if(res.a[i] >= base)
			{
				res.a[i + 1]++;
				res.a[i] -= base;
				while(res.a[res.n + 1])res.n++;
			}
		}
		return res;
	}
	friend INT operator * (const INT &lhs, const INT &rhs)
	{
		INT res;
		res.n = lhs.n + rhs.n - 1;
		for(int i = 1; i <= rhs.n; i++)
			for(int j = 1; j <= lhs.n; j++)
				res.a[i + j - 1] += rhs.a[i] * lhs.a[j];
		for(int i = 1; i <= res.n; i++)
		{
			if(res.a[i] >= base)
			{
				res.a[i + 1] += res.a[i] / base;
				res.a[i] %= base;
				while(res.a[res.n + 1])res.n++;
			}
		}
		return res;
	}
	bool operator > (const INT &rhs)const
	{
		if(n != rhs.n)return n > rhs.n;
		for(int i = n; i >= 1; i--)
			if(a[i] != rhs.a[i])return a[i] > rhs.a[i];
		return false;
	}
	void print(char c)
	{
		if(n == 0)
		{
			printf("0%c", c);
			return;
		}
		printf("%d", a[n]);
		for(int i = n - 1; i >= 1; i--)
			printf("%04d", a[i]);
		putchar(c);
	}
};
INT max(INT a, INT b) { return a > b ? a : b; }
int n, m;
INT a[N], bit[N], f[N][N];
INT ans;
int main()
{
	scanf("%d%d", &n, &m);
	bit[0] = INT(1);
	for(int i = 1; i <= m; i++)bit[i] = bit[i - 1] * INT(2);
	for(int k = 1; k <= n; k++)
	{
		memset(f, 0, sizeof(f));
		for(int i = 1; i <= m; i++)
		{
			int x;
			scanf("%d", &x);
			a[i] = INT(x);
		}
		for(int i = 1; i <= m; i++)
		{
			for(int j = m; j >= i; j--)
			{
				if(i != 1)f[i][j] = max(f[i][j], f[i - 1][j] + a[i - 1] * bit[m - j + i - 1]);
				if(j != m)f[i][j] = max(f[i][j], f[i][j + 1] + a[j + 1] * bit[m - j + i - 1]);
			}
		}
		INT res;
		for(int i = 1; i <= m; i++)
			res = max(res, f[i][i] + a[i] * bit[m]);
		ans = ans + res;
	}
	ans.print('\n');
	return 0;
}
