#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10, mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	ll a[N][N];
	Matrix() {};
	Matrix(int n, int m) : n(n), m(m) { memset(a, 0, sizeof(a)); };
	friend Matrix operator + (const Matrix &a, const Matrix &b)
	{
		Matrix c(a.n, a.m);
		for(int i = 1; i <= a.n; i++)
			for(int j = 1; j <= a.m; j++)
				c.a[i][j] = (a.a[i][j] + b.a[i][j]) % mod;
		return c;
	}
	friend Matrix operator * (const Matrix &a, const Matrix &b)
	{
		Matrix c(a.n, b.m);
		for(int i = 1; i <= a.n; i++)
			for(int j = 1; j <= b.m; j++)
				for(int k = 1; k <= a.m; k++)
					c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
		return c;
	}
	friend Matrix operator ^ (Matrix &a, int n)
	{
		Matrix c(a.n, a.n);
		for(int i = 1; i <= a.n; i++)c.a[i][i] = 1;
		while(n)
		{
			if(n & 1) c = c * a;
			a = a * a;
			n >>= 1;
		}
		return c;
	}
};
/*
1 1 0
0 0 1
1 0 0
*/
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int x;
		scanf("%d", &x);
		if(x <= 3)
		{
			puts("1");
			continue;
		}
		Matrix base(3, 3);
		base.a[1][1] = 1, base.a[3][1] = 1, base.a[1][2] = 1, base.a[2][3] = 1;
		Matrix res(1, 3);
		res.a[1][1] = 1, res.a[1][2] = 1, res.a[1][3] = 1;
		res = res * (base ^ (x - 3));
		printf("%lld\n", res.a[1][1]);
	}
	return 0;
}
