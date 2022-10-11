#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010;
int n, m;
int dis[N];
int maxn = 0, l, r;
namespace solve1
{
	int ans1[N], ans2[N];
	vector<int>e[N];
	void solve()
	{
		for(int i = 1; i <= n; i++)
			dis[i] -= maxn;
		int minn = 0, cl = 0, cr = 0, cnt = 0;
		for(int i = 1; i <= n; i++)
			minn = min(minn, dis[i]);
		for(int i = 1; i <= n; i++)
			if(dis[i] == minn)
				cl = cr, cr = i, cnt++;
		if(cnt > 2)
		{
			puts("NO");
			return;
		}
		memset(ans1, 0, sizeof(ans1));
		memset(ans2, 0, sizeof(ans2));
		for(int i = 1; i <= n; i++)
		{
			int x = -dis[i];
			if(!ans1[x])ans1[x] = i;
			else if(!ans2[x])ans2[x] = i;
			e[x].push_back(i);
		}
		for(int i = 0; i < -minn; i++)
		{
			if(e[i].size() < 2)
			{
				puts("NO");
				return;
			}
		}
		srand(19260817);
		puts("YES");
		if(!ans2[-minn])
		{
			printf("%lld %lld 1\n", ans1[-minn - 1], ans1[-minn]);
			printf("%lld %lld 1\n", ans2[-minn - 1], ans1[-minn]);
			for(auto i : e[-minn - 1])
			{
				if(i == ans1[-minn - 1] || i == ans2[-minn - 1])continue;
				printf("%lld %lld 1\n", i, ans1[-minn]);
			}
		}
		else
		{
			printf("%lld %lld 1\n", ans1[-minn], ans2[-minn]);
			printf("%lld %lld 1\n", ans1[-minn - 1], ans1[-minn]);
			printf("%lld %lld 1\n", ans2[-minn - 1], ans2[-minn]);
			for(auto i : e[-minn - 1])
			{
				if(i == ans1[-minn - 1] || i == ans2[-minn - 1])continue;
				printf("%lld %lld 1\n", i, ans1[-minn]);
			}

		}
		for(int i = -minn - 2; i >= 0; i--)
		{
			printf("%lld %lld 1\n", ans1[i], ans1[i + 1]);
			printf("%lld %lld 1\n", ans2[i], ans2[i + 1]);
			for(auto j : e[i])
			{
				if(j == ans1[i] || j == ans2[i])continue;
				printf("%lld %lld 1\n", j, ans1[i + 1]);
			}
		}
	}
}
namespace solve2
{
	void solve()
	{
		puts("YES");
		int minn = 0, minp = 1;
		for(int i = 2; i <= n; i++)
			if(dis[i] < minn)
				minn = dis[i], minp = i;
		for(int i = 1; i <= n; i++)
		{
			if(i == minp)continue;
			printf("%lld %lld %lld\n", minp, i, dis[i] - minn);
		}
	}
}
signed main()
{
	int ID;
	scanf("%lld%lld", &ID, &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &dis[i]);
	for(int i = 1; i <= n; i++)
		maxn = max(maxn, dis[i]);
	for(int i = 1; i <= n; i++)
		if(dis[i] == maxn)
			l = r, r = i;
	if(!l)
	{
		puts("NO");
		return 0;
	}
	if(ID & 1)solve1::solve();
	else solve2::solve();
	return 0;
}