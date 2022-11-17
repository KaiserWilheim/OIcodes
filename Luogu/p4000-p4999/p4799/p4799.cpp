#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 2000010;
int n;
ll m;
ll a[N];
ll suma[M], sumb[M];
int main()
{
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	int lim = n / 2;
	for(int S = 0; S < (1 << lim); S++)
	{
		ll sum = 0;
		for(int i = 1; i <= lim; i++)
		{
			if(S & (1 << (i - 1)))
				sum += a[i];
		}
		suma[S + 1] = sum;
	}
	for(int S = 0; S < (1 << (n - lim)); S++)
	{
		ll sum = 0;
		for(int i = 1; i <= (n - lim); i++)
		{
			if(S & (1 << (i - 1)))
				sum += a[i + lim];
		}
		sumb[S + 1] = sum;
	}
	int na = 1 << lim, nb = 1 << (n - lim);
	sort(suma + 1, suma + 1 + na);
	sort(sumb + 1, sumb + 1 + nb);
	ll res = 0;
	for(int i = 1; i <= nb; i++)
	{
		if(sumb[i] > m)break;
		int k = upper_bound(suma + 1, suma + 1 + na, m - sumb[i]) - suma - 1;
		res += k;
	}
	printf("%lld\n", res);
	return 0;
}
