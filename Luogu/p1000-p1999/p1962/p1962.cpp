#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10;
const int p = 1e9 + 7;
struct Matrix
{
	int n, m;
	ll a[N][N];
	Matrix() {}
	Matrix(int _n, int _m) :n(_n), m(_m)
	{
		memset(a, 0, sizeof(a));
	}
	Matrix operator * (const Matrix &rhs)
	{
		Matrix res(n, rhs.m);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= rhs.m; j++)
				for(int k = 1; k <= m; k++)
					res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % p;
		return res;
	}
};

Matrix base, res;

void init()
{
	base = Matrix(2, 2);
	base.a[1][1] = 1;
	base.a[1][2] = 1;
	base.a[2][1] = 1;
	res = Matrix(1, 2);
	res.a[1][1] = 1;
	res.a[1][2] = 1;
}

int main()
{
	ll n;
	cin >> n;
	if(n <= 2)
	{
		cout << 1 << endl;
		return 0;
	}
	n -= 2;
	init();
	while(n)
	{
		if(n & 1)
		{
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
	cout << res.a[1][1] << endl;
	return 0;
}
