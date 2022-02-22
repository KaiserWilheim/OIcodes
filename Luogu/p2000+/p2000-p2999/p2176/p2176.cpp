#include<bits/stdc++.h>
using namespace std;
const int N = 110, M = 15010;
int n, m;
int po, ans;
int h[N], e[M], ne[M], w[M], idx = 1;
int dis[N], init[N];
int pre[N], fr[N], edge[M], cnt;

void add(int a, int b, int c)
{
	ne[++idx] = h[a], h[a] = idx, e[idx] = b, w[idx] = c;
}

queue<int> q;
void spfa(int s)
{
	memset(dis, 63, sizeof(dis));
	dis[s] = 0;
	init[s] = 1, q.push(s);
	while(!q.empty())
	{
		int now = q.front(); q.pop(); init[now] = 0;
		for(int i = h[now]; i; i = ne[i])
		{
			int j = e[i];
			if(dis[j] > dis[now] + w[i])
			{
				dis[j] = dis[now] + w[i];
				pre[j] = i; fr[j] = now;
				if(!init[j])
				{
					init[j] = 1; q.push(j);
				}
			}
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	spfa(1);

	po = dis[n];
	int now = n;
	while(now != 1)
	{
		edge[++cnt] = pre[now];
		now = fr[now];
	}
	for(int i = 1; i <= cnt; ++i)
	{
		w[edge[i]] *= 2;
		w[edge[i] ^ 1] *= 2;
		spfa(1);
		ans = max(ans, dis[n]);
		w[edge[i]] /= 2;
		w[edge[i] ^ 1] /= 2;
	}
	printf("%d\n", ans - po);
	return 0;
}
