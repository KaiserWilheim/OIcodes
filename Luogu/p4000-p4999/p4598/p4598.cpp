#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1010;
const int mod = 998244353;
int kpd(int a, int b)
{
	return b ? kpd(b, a % b) : a;
}
int n, m;
int a[N];
vector<int>d[2];
vector<int>rip(int x)
{
	vector<int>res;
	for(int i = 1; i * i <= x; i++)
	{
		if(x % i == 0)
		{
			res.push_back(i);
			if(i * i != x)res.push_back(x / i);
		}
	}
	return res;
}
int f(int x)
{
	int res = 0;
	for(int i = n; i >= 0; i--)
		res = (res * x + a[i]) % mod;
	return res;
}
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
int inv(int x)
{
	int res = qpow(x, mod - 2);
	return res;
}
vector<pair<int, int>>ans;
bool cmp(const pair<int, int> &lhs, const pair<int, int> &rhs)
{
	return lhs.first * rhs.second < lhs.second *rhs.first;
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 0; i <= n; i++)
		scanf("%lld", &a[i]);
	int p = n;
	for(int i = 0; i <= n; i++)
		if(a[i] != 0) { p = i; break; }
	if(p == n)
	{
		puts("0");
		return 0;
	}
	d[0] = rip(abs(a[p])), d[1] = rip(abs(a[n]));
	for(auto i : d[0])
	{
		for(auto j : d[1])
		{
			if(kpd(i, j) == 1)
			{
				int t = inv(j);
				if(f(i * t % mod) == 0)ans.emplace_back(i, j);
				if(f((mod - i) * t % mod) == 0)ans.emplace_back(-i, j);
			}
		}
	}
	if(!a[0])ans.emplace_back(0, 1);
	sort(ans.begin(), ans.end(), cmp);
	printf("%lld\n", ans.size());
	for(auto i : ans)
	{
		if(i.second == 1)printf("%lld\n", i.first);
		else printf("%lld/%lld\n", i.first, i.second);
	}
	return 0;
}