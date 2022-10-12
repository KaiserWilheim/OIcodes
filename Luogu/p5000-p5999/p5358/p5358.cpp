#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
const int mod = 1e7 + 19;
int n, m;
struct Query
{
	int op, k, id;
};
Query q[N];
int add = 0, mul = 1;
int sum = 0;
int ans = 0;
map<int, int>dic;
int getv(int x)
{
	if(!dic.count(x))return add % mod;
	else return (dic[x] * mul % mod + add) % mod;
}
int inv[mod + 1];
signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int op, k = 0, id = 0;
		scanf("%lld", &op);
		if(op == 1 || op == 5)scanf("%lld", &id);
		if(op <= 4)scanf("%lld", &k);
		k = (k % mod + mod) % mod;
		if(op == 3 && k == 0)op = 4;
		q[i] = { op,k,id };
	}
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	int t;
	scanf("%lld", &t);
	for(int _i = 1; _i <= t; _i++)
	{
		int a, b;
		scanf("%lld%lld", &a, &b);
		for(int i = 1; i <= m; i++)
		{
			int idx = (a + i * b) % m + 1;
			int op = q[idx].op;
			if(op == 1)
			{
				int k = getv(q[idx].id);
				sum -= k;
				sum += q[idx].k;
				k = (q[idx].k - add + mod) % mod * inv[mul] % mod;
				dic[q[idx].id] = k;
				sum %= mod;
			}
			else if(op == 2)
			{
				add = (add + q[idx].k) % mod;
				sum = (sum + n * q[idx].k % mod) % mod;
			}
			else if(op == 3)
			{
				mul = mul * q[idx].k % mod;
				add = add * q[idx].k % mod;
				sum = sum * q[idx].k % mod;
			}
			else if(op == 4)
			{
				add = q[idx].k % mod;
				mul = 1;
				sum = add * n % mod;
				dic.clear();
			}
			else if(op == 5)
			{
				int k = getv(q[idx].id);
				ans = (ans + k) % mod;
			}
			else if(op == 6)
			{
				ans = (ans + sum) % mod;
			}
		}
	}
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}