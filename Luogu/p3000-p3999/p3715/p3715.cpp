#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
const ll mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	ll a[N * 2][N * 2];
	Matrix() { memset(a, 0, sizeof(a)); }
	Matrix(int _n, int _m) :n(_n), m(_m) { memset(a, 0, sizeof(a)); }
	friend Matrix operator * (const Matrix &lhs, const Matrix &rhs)
	{
		Matrix res(lhs.n, rhs.m);
		for(int i = 1; i <= lhs.n; i++)
			for(int j = 1; j <= rhs.m; j++)
				for(int k = 1; k <= lhs.m; k++)
					res.a[i][j] = (res.a[i][j] + lhs.a[i][k] * rhs.a[k][j]) % mod;
		return res;
	}
};
struct AK_Avtomat
{
	int s[N][26];
	int fail[N];
	bool end[N];

	int cnt;
	AK_Avtomat() { cnt = 1; }
	void build()
	{
		queue<int>q;
		for(int i = 0; i < 26; i++)
		{
			if(s[1][i])
			{
				q.push(s[1][i]);
				fail[s[1][i]] = 1;
			}
			else
			{
				s[1][i] = 1;
			}
		}
		while(!q.empty())
		{
			int p = q.front();
			q.pop();
			for(int i = 0; i < 26; i++)
			{
				if(s[p][i])
				{
					q.push(s[p][i]);
					fail[s[p][i]] = s[fail[p]][i];
					end[s[p][i]] = end[s[p][i]] || end[fail[s[p][i]]];
				}
				else
				{
					s[p][i] = s[fail[p]][i];
				}
			}
		}
	}
	int add(int p, int c)
	{
		return s[p][c] = (s[p][c]) ? s[p][c] : ++cnt;
	}
	int trv(int p, int c)
	{
		return (end[s[p][c]]) ? -1 : s[p][c];
	}
}tr;
int n, m, l;
char ch[N][N], rd[N];
int len[N];
ll dp[N][N];
int main()
{
	scanf("%d%d%d", &n, &m, &l);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", ch[i] + 1);
		len[i] = strlen(ch[i] + 1);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%s", rd + 1);
		int k = strlen(rd + 1);
		int p = 1;
		for(int j = 1; j <= k; j++)
			p = tr.add(p, rd[j] - 'a');
		tr.end[p] = true;
	}
	tr.build();
	int sz = tr.cnt;
	if(l <= 100)
	{
		dp[0][1] = 1;
		for(int i = 0; i <= l; i++)
		{
			for(int j = 1; j <= sz; j++)
			{
				if(dp[i][j] == 0)continue;
				for(int k = 1; k <= n; k++)
				{
					if(i + len[k] > l)continue;
					int p = j;
					for(int q = 1; q <= len[k] && p != -1; q++)
						p = tr.trv(p, ch[k][q] - 'a');
					if(p != -1)
						dp[i + len[k]][p] = (dp[i + len[k]][p] + dp[i][j]) % mod;
				}
			}
		}
		ll res = 0;
		for(int i = 1; i <= sz; i++)
			res = (res + dp[l][i]) % mod;
		printf("%lld\n", res);
	}
	else
	{
		Matrix st(sz * 2, sz * 2);
		st.a[1][sz + 1] = 1;
		Matrix base(sz * 2, sz * 2);
		for(int i = 1; i <= sz; i++)
			base.a[sz + i][i] = 1;
		for(int i = 1; i <= sz; i++)
		{
			for(int q = 1; q <= n; q++)
			{
				if(len[q] != 1)continue;
				int p = i;
				if(tr.end[p])continue;
				p = tr.trv(p, ch[q][1] - 'a');
				if(p != -1)
					base.a[sz + i][sz + p]++;
			}
		}
		for(int i = 1; i <= sz; i++)
		{
			for(int q = 1; q <= n; q++)
			{
				if(len[q] != 2)continue;
				int p = i;
				if(tr.end[p])continue;
				p = tr.trv(p, ch[q][1] - 'a');
				if(p == -1)continue;
				p = tr.trv(p, ch[q][2] - 'a');
				if(p != -1)
					base.a[i][sz + p]++;
			}
		}
		
		Matrix r(sz * 2, sz * 2);
		for(int i = 1; i <= 2 * sz; i++)
			r.a[i][i] = 1;
		for(int p = l; p; p >>= 1, base = base * base)
			if(p & 1)r = r * base;
		st = st * r;
		ll res = 0;
		for(int i = 1; i <= sz; i++)
			res = (res + st.a[1][sz + i]) % mod;
		printf("%lld\n", res);
	}
	return 0;
}
