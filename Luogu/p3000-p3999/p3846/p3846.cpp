#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int qpow(int a, int x, int p)
{
	int res = 1;
	while(x)
	{
		if(x & 1)res = (res * a) % p;
		a = (a * a) % p;
		x >>= 1;
	}
	return res;
}
int bsgs(int a, int b, int p)
{
	map<int, int>dic;
	dic.clear();
	b %= p;
	int t = sqrt(p) + 1;
	for(int i = 0; i < t; i++)
		dic[b * qpow(a, i, p) % p] = i;
	a = qpow(a, t, p);
	if(!a)return b == 0 ? 1 : -1;
	for(int i = 1; i <= t; i++)
	{
		int v = qpow(a, i, p);
		if(!dic.count(v))continue;
		int j = dic[v];
		if(i * t - j >= 0)return i * t - j;
	}
	return -1;
}
signed main()
{
	int a, b, p;
	scanf("%lld%lld%lld", &p, &a, &b);
	int ans = bsgs(a, b, p);
	if(ans == -1)puts("no solution");
	else printf("%lld\n", ans);
	return 0;
}