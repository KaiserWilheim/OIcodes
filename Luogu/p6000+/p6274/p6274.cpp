#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;
const int mod = 1e9 + 7;
int n;
int prime[N], ct[N];
int sum[(1 << 8) + 1];
#define bs bitset<128>
unordered_map<bs, int>dic;
int dfs(bs st)
{
	if(dic.count(st))return dic[st];
	int res = 1;
	for(int i = 1; i < (1ll << prime[0]); i++)
	{
		bs drei(3);
		int cur = ((st >> (i << 1)) & drei).to_ullong();
		if(cur > 1)continue;
		bs tmp = st;
		for(int j = 0; j < (1ll << prime[0]); j++)
		{
			if(!(i & j))continue;
			if(((st >> (j << 1)) & drei).to_ulong() < 2)
			{
				if(st[j << 1])st.flip((j << 1) + 1);
				else st.flip(j << 1);
			}
		}
		res = (res + dfs(st) * sum[i] % mod) % mod;
		st = tmp;
	}
	dic[st] = res;
	return dic[st];
}
signed main()
{
	scanf("%lld", &n);
	int x = n;
	for(int i = 2; i * i <= x; i++)
	{
		if(x % i != 0)continue;
		prime[++prime[0]] = i;
		while(x % i == 0)x /= i, ct[prime[0]]++;
	}
	if(x > 1)prime[++prime[0]] = x, ct[prime[0]]++;
	for(int S = 0; S < (1ll << prime[0]); S++)
	{
		sum[S] = 1;
		for(int i = 1; i <= prime[0]; i++)
			if(S & (1ll << (i - 1)))
				sum[S] = sum[S] * ct[i] % mod;
	}
	bs tmp;
	int ans = dfs(tmp);
	printf("%lld\n", (ans - 1 + mod) % mod);
	return 0;
}
#undef bs