#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010;
const ll mod = 998244353;
int n, m;
struct Node
{
	int op, v;
};
Node q[N];
ll f[N][N];
ll ans = 0;
void solve(int p)
{
	memset(f, 0, sizeof(f));
	int v = q[p].v;
	f[0][0] = 1;
	for(int i = 1; i < p; i++)
	{
		if(q[i].op == 0)
		{
			for(int j = 0; j <= n; j++)
				f[i][j] = (f[i][j] + f[i - 1][j] + f[i - 1][j + 1]) % mod;
			f[i][0] = (f[i][0] + f[i - 1][0]) % mod;
		}
		else
		{
			if(q[i].v > v)
			{
				for(int j = 0; j <= n; j++)
					f[i][j] = (f[i][j] + f[i - 1][j] * 2) % mod;
			}
			else
			{
				for(int j = 1; j <= n; j++)
					f[i][j] = (f[i][j] + f[i - 1][j] + f[i - 1][j - 1]) % mod;
				f[i][0] = (f[i][0] + f[i - 1][0]) % mod;
			}
		}
	}
	for(int i = 0; i <= n; i++)
		f[p][i] = f[p - 1][i];
	for(int i = p + 1; i <= n; i++)
	{
		if(q[i].op == 0)
		{
			for(int j = 0; j <= n; j++)
				f[i][j] = (f[i][j] + f[i - 1][j] + f[i - 1][j + 1]) % mod;
		}
		else
		{
			if(q[i].v >= v)
			{
				for(int j = 0; j <= n; j++)
					f[i][j] = (f[i][j] + f[i - 1][j] * 2) % mod;
			}
			else
			{
				for(int j = 1; j <= n; j++)
					f[i][j] = (f[i][j] + f[i - 1][j] + f[i - 1][j - 1]) % mod;
				f[i][0] = (f[i][0] + f[i - 1][0]) % mod;
			}
		}
	}
	for(int i = 0; i <= n; i++)
		ans = (ans + f[n][i] * v % mod) % mod;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		string op;
		cin >> op;
		if(op == "-")q[i].op = 0;
		else if(op == "+")
		{
			q[i].op = 1;
			cin >> q[i].v;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(q[i].op == 1)
			solve(i);
	}
	printf("%lld\n", ans);
	return 0;
}