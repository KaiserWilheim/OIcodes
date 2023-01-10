#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 400010;
int n;
vector<int>e[N];
unordered_map<int, int>cnt;
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)e[i].clear();
	cnt.clear();
	for(int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j++)
		{
			int x;
			scanf("%d", &x);
			e[i].push_back(x);
			cnt[x]++;
		}
	}
	bool res = false;
	for(int i = 1; i <= n; i++)
	{
		bool flag = true;
		for(int j = 0; j < e[i].size(); j++)
		{
			if(cnt[e[i][j]] == 1)
			{
				flag = false;
				break;
			}
		}
		if(flag)
		{
			res = true;
			break;
		}
	}
	if(res)puts("Yes");
	else puts("No");
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
