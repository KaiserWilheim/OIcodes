#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll p = 10007;
int n;
int len;
ll a[N];
ll add[N], mul[N];
int id[N];
int main()
{
	scanf("%d", &n);
	len = sqrt(n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		id[i] = (i - 1) / len + 1;
		mul[id[i]] = 1;
	}
	for(int i = 1; i <= n; i++)
	{
		int op, l, r;
		ll c;
		scanf("%d%d%d%lld", &op, &l, &r, &c);
		if(op == 0)
		{
			int lid = id[l], rid = id[r];
			if(lid == rid)
			{
				for(int i = (lid - 1) * len + 1; id[i] == lid; i++)
					a[i] = (a[i] * mul[lid] + add[lid]) % p;
				for(int i = l; i <= r; i++)
					a[i] = (a[i] + c) % p;
				mul[lid] = 1, add[lid] = 0;
				continue;
			}
			for(int i = (lid - 1) * len + 1; id[i] == lid; i++)
				a[i] = (a[i] * mul[lid] + add[lid]) % p;
			for(int i = l; id[i] == lid; i++)
				a[i] = (a[i] + c) % p;
			for(int i = lid + 1; i < rid; i++)
				add[i] = (add[i] + c) % p;
			for(int i = (rid - 1) * len + 1; id[i] == rid; i++)
				a[i] = (a[i] * mul[rid] + add[rid]) % p;
			for(int i = r; id[i] == rid; i--)
				a[i] = (a[i] + c) % p;
			mul[lid] = mul[rid] = 1;
			add[lid] = add[rid] = 0;
		}
		else if(op == 1)
		{
			int lid = id[l], rid = id[r];
			if(lid == rid)
			{
				for(int i = (lid - 1) * len + 1; id[i] == lid; i++)
					a[i] = (a[i] * mul[lid] + add[lid]) % p;
				for(int i = l; i <= r; i++)
					a[i] = (a[i] * c) % p;
				mul[lid] = 1, add[lid] = 0;
				continue;
			}
			for(int i = (lid - 1) * len + 1; id[i] == lid; i++)
				a[i] = (a[i] * mul[lid] + add[lid]) % p;
			for(int i = l; id[i] == lid; i++)
				a[i] = (a[i] * c) % p;
			for(int i = lid + 1; i < rid; i++)
			{
				mul[i] = (mul[i] * c) % p;
				add[i] = (add[i] * c) % p;
			}
			for(int i = (rid - 1) * len + 1; id[i] == rid; i++)
				a[i] = (a[i] * mul[rid] + add[rid]) % p;
			for(int i = r; id[i] == rid; i--)
				a[i] = (a[i] * c) % p;
			mul[lid] = mul[rid] = 1;
			add[lid] = add[rid] = 0;
		}
		else if(op == 2)
		{
			ll res = (a[r] * mul[id[r]] + add[id[r]]) % p;
			printf("%lld\n", res);
		}
	}
	return 0;
}
