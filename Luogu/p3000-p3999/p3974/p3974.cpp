#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, m;
int res[N], sta[N], tt;
void solve()
{
	int ans = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		tt = 1, sta[tt] = 0, res[0] = 1e9;
		for(int j = 1; j <= m; j++)
		{
			int a;
			scanf("%d", &a);
			if(a > res[j])
			{
				int del = a - res[j];
				while(res[sta[tt]] < del)
					del -= res[sta[tt]], res[sta[tt--]] = 0;
				res[sta[tt]] -= del;
				res[j] = a;
			}
			sta[++tt] = j;
		}
		ans += 1e9 - res[0];
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(res, 0, sizeof(res));
		solve();
	}
	return 0;
}