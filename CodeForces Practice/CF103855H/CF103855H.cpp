#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
const ll mod = 1e9 + 7;
int n;
int a[N], b[N], cnt;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] > maxn)b[++cnt] = i;
		maxn = max(maxn, a[i]);
	}
	ll res = 1;
	for(int i = 1; i < cnt; i++)
		res = (res * (b[i + 1] - b[i] + 1)) % mod;
	printf("%lld\n", res);
	return 0;
}
