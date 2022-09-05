#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 110;
const int mod = 1e9 + 7;
int n, a, p, q;
int P, inv;
int f[N], g[N];
struct Matrix
{
	int mat[N][N];
	Matrix() { memset(mat, 0, sizeof(mat)); }
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res;
		for(int k = 1; k <= a + 2; k++)
			for(int i = 1; i <= a + 2; i++)
				for(int j = 1; j <= a + 2; j++)
					res.mat[i][j] = (res.mat[i][j] + lhs.mat[i][k] * rhs.mat[k][j]) % mod;
		return res;
	}
};
Matrix F, G;
int qpow(int a, int x)
{
	int res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return res;
}
Matrix mpow(Matrix A, int x)
{
	Matrix res;
	for(int i = 1; i <= a + 2; i++)res.mat[i][i] = 1;
	while(x)
	{
		if(x & 1)res = res * A;
		A = A * A;
		x >>= 1;
	}
	return res;
}
signed main()
{
	cin >> n >> a >> p >> q;
	P = p * qpow(q, mod - 2) % mod;
	inv = qpow(P, mod - 2);
	if(P == 1)
	{
		cout << n % mod << endl;
		return 0;
	}
	else if(a == 0)
	{
		cout << n % mod * inv % mod << endl;
		return 0;
	}
	else if(a == n)
	{
		cout << (qpow(inv, n + 1) - inv + mod) % mod * qpow((inv - 1 + mod) % mod, mod - 2) % mod << endl;
		return 0;
	}

	for(int i = 0; i <= a; i++)
	{
		int t = 0;
		for(int j = 0; j < i; j++)
			t = (t + f[j]) % mod;
		f[i] = (inv + (inv - 1) * t) % mod;
	}
	g[0] = f[0];
	for(int i = 1; i <= a; i++)g[i] = (g[i - 1] + f[i]) % mod;

	for(int i = 1; i <= a + 1; i++)
		F.mat[i][1] = g[a - i + 1];
	F.mat[a + 2][1] = inv;
	G.mat[1][1] = inv;
	G.mat[1][a + 1] = mod - inv + 1;
	G.mat[1][a + 2] = 1;
	for(int i = 2; i <= a + 1; i++)G.mat[i][i - 1] = 1;
	G.mat[a + 2][a + 2] = 1;
	F = mpow(G, n - 1) * F;
	cout << F.mat[a + 1][1] << endl;
	return 0;
}