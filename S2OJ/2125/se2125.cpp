#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 20;
ll mod = 998444353;
ll inv2, inv3;
ll qpow(ll a, ll x)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}
ll add(ll a, ll b)
{
	return a + b >= mod ? a + b - mod : a + b;
}
int n, m;
struct Matrix
{
	ll a[N][N];
	Matrix() { memset(a, 0, sizeof(a)); }
	Matrix(ll _v)
	{
		memset(a, 0, sizeof(a));
		for(int i = 0; i <= m; i++)a[i][i] = _v;
	}
	ll *operator [] (int i) { return a[i]; }
	friend Matrix operator * (Matrix lhs, Matrix rhs)
	{
		Matrix res(0);
		for(int k = 0; k <= m; k++)
			for(int i = 0; i <= m; i++)
				for(int j = 0; j <= m; j++)
					res[i][j] = add(res[i][j], lhs[i][k] * rhs[k][j] % mod);
		return res;
	}
};
Matrix qpow(Matrix a, ll x)
{
	Matrix res(1);
	while(x)
	{
		if(x & 1)res = res * a;
		a = a * a;
		x >>= 1;
	}
	return res;
}
Matrix A, B;
int main()
{
	inv2 = qpow(2, mod - 2), inv3 = qpow(3, mod - 2);
	int b, p;
	scanf("%d%d%d", &n, &m, &b);
	p = 1;
	if(b == 10)b = 5;
	if(b == 9)b = 3, p = 2;
	if(b == 8)b = 2, p = 3;
	if(b == 6)b = 3;
	if(b == 4)b = 2, p = 2;
	mod *= p;
	for(int i = 0; i <= m; i++)
		for(int j = i; j <= m; j++)
			A[i][j] = 1;
	A[0][0] = 0;
	ll ans = 0;
	for(ll i = b; i <= n; i *= b)
	{
		B = qpow(A, i);
		B[0][0] = 1;
		Matrix res = qpow(B, n / i - 1) * qpow(A, n % i);
		for(int j = 0; j <= m; j++)ans = add(ans, res[0][j]);
	}
	ans /= p;
	printf("%lld\n", ans);
	return 0;
}
