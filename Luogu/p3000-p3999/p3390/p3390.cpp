#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
const ll p = 1e9 + 7;
struct Matrix
{
	int n;
	ll a[N][N];
	Matrix() {}
	Matrix(int _n) :n(_n)
	{
		memset(a, 0, sizeof(a));
	}
	void input()
	{
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				cin >> a[i][j];
	}
	void output()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
				cout << a[i][j] << " ";
			cout << endl;
		}
	}
	Matrix operator * (const Matrix &rhs)
	{
		Matrix res(n);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= rhs.n; j++)
				for(int k = 1; k <= n; k++)
					res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % p;
		return res;
	}
	Matrix operator ^ (ll x)
	{
		Matrix res(n), bas(n);
		for(int i = 1; i <= n; i++)
			res.a[i][i] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				bas.a[i][j] = a[i][j] % p;
		while(x)
		{
			if(x & 1)res = res * bas;
			bas = bas * bas;
			x >>= 1;
		}
		return res;
	}
};
int main()
{
	int n;
	ll k;
	cin >> n >> k;
	Matrix base(n);
	base.input();
	base = base ^ k;
	base.output();
	return 0;
}
