#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
int n, m;
int a[N];
int sta[N], cnt[N], tt;
ll ans;
signed main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		while(tt && sta[tt] < a[i])
		{
			ans += cnt[tt];
			tt--;
		}
		if(tt && sta[tt] == a[i])
			ans += cnt[tt], cnt[tt]++;
		else sta[++tt] = a[i], cnt[tt] = 1;
		if(tt > 1)ans++;
	}
	printf("%lld\n", ans);
	return 0;
}
