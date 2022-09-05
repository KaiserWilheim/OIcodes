#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
struct kyon
{
	int w, s;
	bool operator < (const kyon &a) const
	{
		return w + s < a.w + a.s;
	}
}ky[N];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &ky[i].w, &ky[i].s);
	sort(ky + 1, ky + n + 1);
	ll ans = -1e18, prf = 0;
	for(int i = 1; i <= n; i++)
	{
		ans = max(ans, prf - ky[i].s);
		prf += ky[i].w;
	}
	printf("%lld\n", ans);
	return 0;
}