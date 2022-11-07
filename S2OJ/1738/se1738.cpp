#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010, K = 110;
const ll mod = 1e9 + 7;
ll n, m, k;
int a[N];
ll ans;
int ls[K];
ll f[N];
struct Node
{
	int pr, x;
	Node(int _p, int _x) { pr = _p, x = _x; }
	bool operator < (const Node &rhs)const
	{
		return pr > rhs.pr;
	}
};
struct Matrix
{
	int n, m;
	ll a[K][K];
	Matrix() {};
	Matrix(int _n, int _m)
	{
		n = _n, m = _m;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				a[i][j] = 0;
	};
	friend Matrix operator * (const Matrix &a, const Matrix &b)
	{
		Matrix c(a.n, b.m);
		for(int i = 1; i <= a.n; i++)
			for(int j = 1; j <= b.m; j++)
				for(int k = 1; k <= a.m; k++)
					c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
		return c;
	}
	friend Matrix operator ^ (Matrix a, ll n)
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
int main()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		if(ls[a[i]])f[i] = 2 * f[i - 1] - f[ls[a[i]] - 1];
		else f[i] = 2 * f[i - 1] + 1;
		ls[a[i]] = i;
		f[i] = (f[i] % mod + mod) % mod;
	}
	if(m == 0)
	{
		printf("%lld\n", f[n]);
		return 0;
	}
	priority_queue<Node>q;
	for(int i = 1; i <= k; i++)
		q.emplace(ls[i], i);
	if(m <= k)
	{
		for(int i = 1; i <= m; i++)
		{
			Node now = q.top();
			q.pop();
			if(now.pr)f[n + i] = 2 * f[n + i - 1] - f[now.pr - 1];
			else f[n + i] = 2 * f[n + i - 1] + 1;
			f[n + i] = (f[n + i] % mod + mod) % mod;
			ls[now.x] = n + i;
			q.emplace(n + i, now.x);
		}
		printf("%lld\n", f[n + m]);
		return 0;
	}
	for(int i = 1; i <= k; i++)
	{
		Node now = q.top();
		q.pop();
		if(now.pr)f[n + i] = 2 * f[n + i - 1] - f[now.pr - 1];
		else f[n + i] = 2 * f[n + i - 1] + 1;
		f[n + i] = (f[n + i] % mod + mod) % mod;
	}
	Matrix res(1, k + 1);
	for(int i = 1; i <= k + 1; i++)
		res.a[1][i] = f[n + k - i + 1];
	Matrix x(k + 1, k + 1);
	x.a[1][1] = 2, x.a[k + 1][1] = mod - 1;
	for(int i = 1; i <= k; i++)
		x.a[i][i + 1] = 1;
	x = x ^ (m - k);
	res = res * x;
	ans = res.a[1][1];
	printf("%lld\n", ans);
	return 0;
}