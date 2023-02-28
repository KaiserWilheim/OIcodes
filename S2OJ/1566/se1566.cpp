#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010;
int n, k;
ll a[N], b[N];
void solve()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	for(int i = n; i; i--)
		a[i] -= a[i - 1], b[i] -= b[i - 1];
	for(int i = 1; i <= n - k + 1; i++)
	{
		if(a[i] == b[i])continue;
		b[i + k] -= a[i] - b[i];
		b[i] = a[i];
	}
	bool flag = true;
	for(int i = 1; i <= n; i++)
		if(a[i] != b[i])flag = false;
	if(flag)puts("YES");
	else puts("N0");
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
