#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = 500010;
int h[N], e[M], ne[M], w[M], idx;
int tot[N], dis[N], vis[N];
int n, m;
void add(int a, int b, int c)
{
	e[++idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}
bool spfa(int s)
{
	queue<int> q;
	memset(dis, 63, sizeof(dis));
	dis[s] = 0, vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				if(!vis[v])
				{
					vis[v] = 1, tot[v]++;
					if(tot[v] == n + 1)return false;
					q.push(v);
				}
			}
		}
	}
	return true;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= 50001; i++)
	{
		add(i - 1, i, 0);
		add(i, i - 1, 1);
	}
	for(int i = 1; i <= n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b + 1, -c);
	}
	spfa(0);
	printf("%d\n", -dis[50001]);
	return 0;
}
