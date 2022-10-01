#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 55;
const int mod = 10000;
int n, m;
struct Matrix
{
	int a[N][N];
	Matrix()
	{
		memset(a, 0, sizeof(a));
	}
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					res.a[i][j] = (res.a[i][j] + lhs.a[i][k] * rhs.a[k][j] % mod) % mod;
		return res;
	}
};
Matrix a[15];
Matrix G;
Matrix base;
int st, ed;
ll k;
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
	scanf("%d%d", &n, &m);
	scanf("%d%d%lld", &st, &ed, &k);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G.a[u][v] = G.a[v][u] = 1;
	}
	for(int i = 1; i <= 12; i++)a[i] = G;
	for(int i = 0; i < n; i++)base.a[i][i] = 1;
	int f;
	scanf("%d", &f);
	for(int i = 1; i <= f; i++)
	{
		int t, tmpt[N];
		scanf("%d", &t);
		for(int i = 0; i < t; i++)scanf("%d", &tmpt[i]);
		tmpt[t] = tmpt[0];
		for(int i = 1; i <= 12; i++)
			for(int j = 0; j < n; j++)
				a[i].a[j][tmpt[(i - 1) % t + 1]] = 0;
	}
	a[0] = base;
	for(int i = 1; i <= 12; i++)a[0] = a[0] * a[i];
	Matrix res = qpow(a[0], k / 12);
	for(int i = 1; i <= k % 12; i++)res = res * a[i];
	printf("%d\n", res.a[st][ed]);
	return 0;
}