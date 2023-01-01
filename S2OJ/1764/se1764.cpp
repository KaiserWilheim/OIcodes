#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
struct bint
{
	int n;
	short a[110];
	bint()
	{
		n = 1;
		memset(a, 0, sizeof(a));
	}
	bint(string s)
	{
		n = s.length();
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= n; i++)
			a[i] = s[i - 1] - '0';
	}
	friend bint operator + (const bint &lhs, const bint &rhs)
	{
		bint res;
		res.n = max(lhs.n, rhs.n);
		for(int i = 1; i <= res.n; i++)
			res.a[i] = lhs.a[i] + rhs.a[i];
		for(int i = 1; i <= res.n; i++)
		{
			if(res.a[i] > 9)
			{
				res.a[i + 1]++;
				res.a[i] -= 10;
				if(i == res.n)res.n++;
			}
		}
		return res;
	}
	friend bint operator * (const bint &lhs, const int &rhs)
	{
		bint res;
		res.n = lhs.n;
		for(int i = 1; i <= res.n; i++)
			res.a[i] = lhs.a[i] * rhs;
		for(int i = 1; i <= res.n; i++)
		{
			if(res.a[i] > 9)
			{
				res.a[i + 1] += res.a[i] / 10;
				res.a[i] %= 10;
				if(i == res.n)res.n++;
			}
		}
		return res;
	}
	void print(char c)
	{
		for(int i = n; i >= 1; i--)
			cout << a[i];
		putchar(c);
	}
};
int n, m;
int h[N], e[M], ne[M], pos[M], idx;
bint w[N];
void add(int a, int b, int c)
{
	e[idx] = b, pos[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int st[N];
bint sum[N];
void dfs(int p, int fa)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		sum[p] = sum[p] + sum[e[i]];
		sum[p] = sum[p] + (w[pos[i]] * abs(st[e[i]]));
		st[p] += st[e[i]];
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	memset(h, -1, sizeof(h));
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;
		st[x]++;
	}
	for(int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;
		st[x]--;
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		string s;
		cin >> u >> v >> s;
		w[i] = bint(s);
		add(u, v, i), add(v, u, i);
	}
	dfs(1, 0);
	sum[1].print('\n');
	return 0;
}