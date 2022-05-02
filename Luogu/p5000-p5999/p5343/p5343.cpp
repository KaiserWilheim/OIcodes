#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100, mod = 1e9 + 7;
int n, n1, n2;
set<int>p;
int v[N], cnt;
int maxlen;
int f[N];
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
		for(int i = 1; i <= maxlen; i++)
			for(int j = 1; j <= maxlen; j++)
				for(int k = 1; k <= maxlen; k++)
					res.a[i][j] = (res.a[i][j] + (lhs.a[i][k] * rhs.a[k][j]) % mod) % mod;
		return res;
	}
}base, a;

Matrix qpow(Matrix a, int y)
{
	Matrix z = base;
	while(y)
	{
		if(y & 1)
			z = z * a;
		a = a * a;
		y >>= 1;
	}
	return z;
}

signed main()
{
	cin >> n >> n1;
	for(int i = 1; i <= n1; i++)
	{
		int x;
		cin >> x;
		p.insert(x);
	}
	cin >> n2;
	int tot = 0;
	for(int i = 1; i <= n2; i++)
	{
		int x;
		cin >> x;
		if(p.count(x))
		{
			v[++tot] = x;
			maxlen = max(maxlen, x);
		}
	}
	sort(v + 1, v + 1 + tot);
	cnt = unique(v + 1, v + 1 + tot) - v - 1;
	f[0] = 1;
	for(int i = 1; i <= maxlen; i++)
	{
		for(int k = 1; k <= cnt; k++)
		{
			int j = v[k];
			if(!j)continue;
			if(j > i)break;
			f[i] = (f[i] + f[i - j]) % mod;
		}
	}
	if(n <= maxlen)
	{
		cout << f[n] << endl;
		return 0;
	}
	Matrix ans;
	for(int i = 1; i <= maxlen; i++)
	{
		base.a[i][i] = 1;
		ans.a[i][1] = f[i];
		a.a[i][i + 1] = 1;
	}
	for(int i = 1; i <= cnt; i++)
	{
		int j = v[i];
		a.a[maxlen][maxlen - j + 1] = 1;
	}
	ans = qpow(a, n - maxlen) * ans;
	cout << ans.a[maxlen][1] << endl;
	return 0;
}
