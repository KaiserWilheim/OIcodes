#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3;
const ll mod = 1e9 + 7;
ll n, k;
struct Matrix
{
	ll a[N][N];
	Matrix() { memset(a, 0, sizeof(a)); }
	friend Matrix operator - (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res;
		for(int i = 1; i <= 2; i++)
			for(int j = 1; j <= 2; j++)
				res.a[i][j] = (lhs.a[i][j] - rhs.a[i][j] + mod) % mod;
		return res;
	}
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res;
		for(int i = 1; i <= 2; i++)
			for(int j = 1; j <= 2; j++)
				for(int k = 1; k <= 2; k++)
					res.a[i][j] = (res.a[i][j] + lhs.a[i][k] * rhs.a[k][j]) % mod;
		return res;
	}
};
Matrix A, B, base;
void init()
{
	base.a[1][1] = base.a[2][2] = 1;
	A.a[1][1] = 1;
	B.a[1][1] = B.a[1][2] = B.a[2][1] = 1;
}
Matrix qpow(Matrix a, ll x)
{
	Matrix res = base;
	while(x)
	{
		if(x & 1)res = res * a;
		a = a * a;
		x >>= 1;
	}
	return res;
}
int main()
{
	int T;
	scanf("%d", &T);
	init();
	while(T--)
	{
		scanf("%lld%lld", &n, &k);
		Matrix res = A * qpow(qpow(B, n + 1) - B, k);
		printf("%lld\n", res.a[1][1]);
	}
	return 0;
}