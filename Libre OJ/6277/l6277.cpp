#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int len;
ll a[N];
ll tag[N];
int id[N];
int main()
{
	scanf("%d", &n);
	len = sqrt(n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		id[i] = (i - 1) / len + 1;
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
				for(int i = l; i <= r; i++)
					a[i] += c;
				continue;
			}
			for(int i = l; id[i] == lid; i++)
				a[i] += c;
			for(int i = lid + 1; i < rid; i++)
				tag[i] += c;
			for(int i = r; id[i] == rid; i--)
				a[i] += c;
		}
		else if(op == 1)
		{
			printf("%lld\n", a[r] + tag[id[r]]);
		}
	}
	return 0;
}
