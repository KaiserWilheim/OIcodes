#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int cnt[N];
int pos[N];
vector<int>e[N];
bool vis[N];
void add(int a, int b)
{
	e[a].push_back(b);
}
void dfs(int p)
{
	vis[p] = true;
	for(auto j : e[p])
		if(!vis[j])dfs(j);
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)cnt[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		pos[x] = i;
		cnt[(i - x + n) % n]++;
	}
	vector<int>ans;
	for(int k = 0; k < n; k++)
	{
		if(cnt[k] < n - 2 * m)continue;
		for(int i = 1; i <= n; i++)
			vis[i] = false, e[i].clear();
		for(int i = 1; i <= n; i++)
		{
			int now = (i + k - 1) % n + 1;
			if(now != pos[i])add(now, pos[i]);
		}
		int c = 0;
		for(int i = 1; i <= n; i++)
		{
			int now = (i + k - 1) % n + 1;
			if(now != pos[i] && !vis[now])
			{
				dfs(now);
				c++;
			}
		}
		if(n - cnt[k] - c <= m)ans.push_back(k);
	}
	printf("%d ", ans.size());
	for(auto i : ans)
		printf("%d ", i);
	putchar('\n');
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