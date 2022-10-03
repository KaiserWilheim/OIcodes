#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int cnt;
int a[N];
bool chq()
{
	if(a[1] == 1)return false;
	for(int i = 2; i <= cnt; i++)
		if(a[i] % a[1] != 0)return true;
	return false;
}
int dis[N];
bool vis[N];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	cnt = n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i] - j > 0)a[++cnt] = a[i] - j;
	sort(a + 1, a + 1 + cnt);
	if(!chq())
	{
		puts("-1");
		return 0;
	}
	cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	memset(dis, 63, sizeof(dis));
	dis[0] = 0;
	queue<int>q;
	q.push(0);
	vis[0] = true;
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = 2; i <= cnt; i++)
		{
			if(dis[(p + a[i]) % a[1]] > dis[p] + a[i])
			{
				dis[(p + a[i]) % a[1]] = dis[p] + a[i];
				if(!vis[(p + a[i]) % a[1]])
				{
					vis[(p + a[i]) % a[1]] = true;
					q.push((p + a[i]) % a[1]);
				}
			}
		}
		vis[p] = false;
	}
	int ans = 0;
	for(int i = 1; i <= a[1] - 1; i++)
		ans = max(ans, dis[i]);
	printf("%d\n", ans - a[1]);
	return 0;
}