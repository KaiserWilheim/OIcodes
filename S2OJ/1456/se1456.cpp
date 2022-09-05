#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, M = N << 1;
const ll mod = 998244353;
int n, k;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
vector<int>kmp(string s)
{
	int n = (int)s.length();
	vector<int>pi(n);
	for(int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while(j > 0 && s[i] != s[j])j = pi[j - 1];
		if(s[i] == s[j])j++;
		pi[i] = j;
	}
	return pi;
}
int sta[N], hh, tt;
int tr[N];
ll ans = 1;
void dfs(int p)
{
	sta[++tt] = p;
	tr[p * 2 % k]++;
	ll tmp = hh;
	while(hh < tt)
	{
		if(2 * sta[hh] >= p + 1)break;
		tr[sta[hh++] * 2 % k]--;
	}
	ans = (ans * (tr[p % k] + 1)) % mod;
	for(int i = h[p]; ~i; i = ne[i])
		dfs(e[i]);
	for(int i = hh - 1; i >= tmp; i--)
		tr[sta[i] * 2 % k]++;
	hh = tmp;
	tr[p * 2 % k]--;
	tt--;
}
int main()
{
	memset(h, -1, sizeof(h));
	string s;
	cin >> s;
	cin >> k;
	vector<int>pi = kmp(s);
	n = s.length();
	for(int i = 1; i <= n; i++)
	{
		add(pi[i - 1], i);
	}
	for(int i = h[0]; ~i; i = ne[i])
	{
		hh = 1, tt = 0;
		dfs(e[i]);
	}
	printf("%lld\n", ans);
	return 0;
}