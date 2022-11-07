#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
char a[N], b[N];
int cnta[N], cntb[N];
int main()
{
	cin >> a + 1 >> b + 1;
	n = strlen(a + 1), m = strlen(b + 1);
	ll ans = 1ll * (n + 1) * (m + 1);
	for(int i = 1; i <= n; i++)
		cnta[a[i] - 'a']++;
	for(int i = 1; i <= m; i++)
		cntb[b[i] - 'a']++;
	for(int i = 0; i < 26; i++)
		ans -= 1ll * cnta[i] * cntb[i];
	printf("%lld\n", ans);
	return 0;
}