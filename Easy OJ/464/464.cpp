#include<bits/stdc++.h>
using namespace std;
const int N = 100;
#define ll long long
int a[N], b[N];
int n;
ll ans = 0;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n, greater<int>());
	int l = n / 2 + 1, r = n / 2 + 1, o = 0;
	b[l] = a[1];
	for(int i = 2; i <= n; i++)
		(!o ? b[--l] : b[++r]) = a[i], o ^= 1;
	for(int i = 1; i <= n; i++)
		ans += 1ll * b[i] * b[i + 1];
	printf("%lld\n", ans);
	return 0;
}
