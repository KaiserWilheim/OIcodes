#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010, M = N << 1;
int n, m;
int h[N], e[M], ne[M], idx;
int color[N];
bool flag = true;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int cc[N], sc;
void paint(int s)
{
	queue<int>q;
	color[s] = 2;
	q.push(s);
	cc[s] = ++sc;
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(color[e[i]] == color[p])
			{
				flag = false;
				return;
			}
			if(color[e[i]])continue;
			color[e[i]] = color[p] ^ 1;
			cc[e[i]] = sc;
			q.push(e[i]);
		}
	}
}
int dis[N];
int dep[N];
void run(int s)
{
	memset(dis, 0, sizeof(dis));
	queue<int>q;
	dis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = h[p]; ~i; i = ne[i])
		{
			if(dis[e[i]] && dis[e[i]] <= dis[p] + 1)continue;
			dis[e[i]] = dis[p] + 1;
			dep[cc[p]] = max(dep[cc[p]], dis[p]);
			q.push(e[i]);
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);

	}
	for(int i = 1; i <= n; i++)
	{
		if(!color[i])paint(i);
		if(!flag)
		{
			puts("-1");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++)
		run(i);
	int sum = 0;
	for(int i = 1; i <= sc; i++)
		sum += dep[i];
	printf("%d\n", sum);
	return 0;
}