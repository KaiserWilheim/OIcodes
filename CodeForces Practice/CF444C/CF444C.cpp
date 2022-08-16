#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 450;
int n, m;
ll S;
ll a[N], b[N];
ll ta[M], tb[M], sa[M];
int main()
{
	scanf("%d%d", &n, &m);
	S = sqrt(n);
	for(int i = 0; i < n; i++)
		a[i] = i + 1;
	while(m--)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		l--, r--;
		if(op == 1)
		{
			ll k;
			scanf("%lld", &k);
			int tl = l / S, tr = r / S;
			if(tl == tr)
			{
				if(ta[tl])
				{
					for(int i = tr * S; i < (tr + 1) * S; i++)
						a[i] = ta[tl];
					ta[tl] = 0;
				}
				for(int i = l; i <= r; i++)
				{
					b[i] += abs(k - a[i]);
					sa[tl] += abs(k - a[i]);
					a[i] = k;
				}
			}
			else
			{
				if(ta[tl])
				{
					for(int i = tl * S; i < (tl + 1) * S; i++)
						a[i] = ta[tl];
					ta[tl] = 0;
				}
				for(int i = l; i < (tl + 1) * S; i++)
				{
					b[i] += abs(k - a[i]);
					sa[tl] += abs(k - a[i]);
					a[i] = k;
				}
				for(int i = tl + 1; i < tr; i++)
				{
					if(ta[i])
					{
						tb[i] += abs(k - ta[i]);
						sa[i] += abs(k - ta[i]) * S;
					}
					else
					{
						for(int j = i * S; j < (i + 1) * S; j++)
						{
							b[j] += abs(k - a[j]);
							sa[i] += abs(k - a[j]);
							a[j] = k;
						}
					}
					ta[i] = k;
				}
				if(ta[tr])
				{
					for(int i = tr * S; i < (tr + 1) * S; i++)
						a[i] = ta[tr];
					ta[tr] = 0;
				}
				for(int i = tr * S; i <= r; i++)
				{
					b[i] += abs(k - a[i]);
					sa[tr] += abs(k - a[i]);
					a[i] = k;
				}
			}
		}
		else
		{
			ll sum = 0;
			int tl = l / S, tr = r / S;
			if(tl == tr)
			{
				for(int i = l; i <= r; i++)
					sum += tb[tl] + b[i];
			}
			else
			{
				for(int i = l; i < (tl + 1) * S; i++)
					sum += tb[tl] + b[i];
				for(int i = tl + 1; i < tr; i++)
					sum += sa[i];
				for(int i = tr * S; i <= r; i++)
					sum += tb[tr] + b[i];
			}
			printf("%lld\n", sum);
		}
	}
	return 0;
}
