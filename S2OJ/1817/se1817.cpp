#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 160, M = N << 1;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll x = mod - 2)
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
int n;
struct Node
{
	int c[26];
	int end;
	int fail;
};
Node tr[N];
int idx;
void insert(string s)
{
	int p = 1;
	for(int i = 0; i < s.length(); i++)
	{
		if(!tr[p].c[s[i] - 'a'])tr[p].c[s[i] - 'a'] = ++idx;
		p = tr[p].c[s[i] - 'a'];
	}
	tr[p].end = 1;
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 26; i++)
	{
		if(tr[1].c[i])q.push(tr[1].c[i]), tr[tr[1].c[i]].fail = 1;
		else tr[1].c[i] = 1;
	}
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
		{
			if(tr[p].c[i])
			{
				tr[tr[p].c[i]].fail = tr[tr[p].fail].c[i];
				q.push(tr[p].c[i]);
			}
			else
			{
				tr[p].c[i] = tr[tr[p].fail].c[i];
			}
		}
	}
}
ll add(ll a, ll b)
{
	return a + b >= mod ? a + b - mod : a + b;
}
ll a[N][N];
void GaussJordan(int n)
{
	for(int i = 1; i <= n; i++)
	{
		if(!a[i][i])
		{
			for(int j = i + 1; j <= n; j++)
			{
				if(a[j][i])
				{
					swap(a[i], a[j]);
					break;
				}
			}
		}
		ll b = qpow(a[i][i]);
		for(int k = 1; k <= n; k++)
		{
			if(k == i)continue;
			ll p = a[k][i] * b % mod;
			for(int j = i; j <= n + 1; j++)
				a[k][j] = add(a[k][j], mod - p * a[i][j] % mod);
		}
	}
}
void solve()
{
	idx = 1;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		insert(s);
	}
	get_fail();
	for(int i = 1; i <= idx; i++)
	{
		a[i][i] = 1;
		if(tr[i].end)continue;
		a[i][idx + 1] = 1;
		for(int j = 0; j < 26; j++)
			a[i][tr[i].c[j]] = add(a[i][tr[i].c[j]], mod - qpow(26));
	}
	GaussJordan(idx);
	printf("%lld\n", a[1][idx + 1] * qpow(a[1][1]) % mod);
	for(int i = 1; i <= idx; i++)
		for(int j = 1; j <= idx + 1; j++)
			a[i][j] = 0;
	for(int i = 1; i <= idx; i++)
	{
		tr[i].end = tr[i].fail = 0;
		for(int j = 0; j < 26; j++)
			tr[i].c[j] = 0;
	}
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}
