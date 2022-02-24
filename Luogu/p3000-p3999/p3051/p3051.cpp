#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
ll n, m, ans;
ll a[N], b[N], c[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%lld%lld", &a[i], &b[i]);
	for(int i = 2; i <= n; i++)c[i] = c[i - 1] + b[i - 1] - a[i - 1];
	sort(c + 1, c + n + 1);
	m = 0 - c[(n + 1) / 2];
	for(int i = 1; i <= n; i++)ans += abs(c[i] + m);
	printf("%lld", ans);
	return 0;
}
