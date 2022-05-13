#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 30010;
int n, m;
vector<int>e[N];
int dis[N], vis[N];
queue<int>q;
void spfa(int s)
{
	memset(dis, 63, sizeof(dis));
	dis[s] = 0, vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(auto i : e[u])
		{
			for(int j = 1; u + i * j < n; j++)
			{
				int v = u + i * j;
				if(dis[v] > dis[u] + j)
				{
					dis[v] = dis[u] + j;
					if(!vis[v])
					{
						q.push(v);
						vis[v] = 1;
					}
				}
			}
			for(int j = 1; u - i * j >= 0; j++)
			{
				int v = u - i * j;
				if(dis[v] > dis[u] + j)
				{
					dis[v] = dis[u] + j;
					if(!vis[v])
					{
						q.push(v);
						vis[v] = 1;
					}
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	int s, t;
	for(int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(i == 0)s = a;
		if(i == 1)
		{
			t = a;
			continue;
		}
		e[a].push_back(b);
	}
	spfa(s);
	if(dis[t] == 0x3f3f3f3f)puts("-1");
	else cout << dis[t] << endl;
	return 0;
}
