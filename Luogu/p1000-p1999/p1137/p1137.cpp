#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 200010;
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int top[N], deg[N], tot;
void topsort()
{
	queue<int>q;
	for(int i = 1; i <= n; i++)
	{
		if(deg[i] == 0)
		{
			q.push(i);
			top[++tot] = i;
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			deg[v]--;
			if(deg[v] == 0)
			{
				q.push(v);
				top[++tot] = v;
			}
		}
	}
}
int dp[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		deg[b]++;
	}
	topsort();
	for(int i = 1; i <= n; i++)dp[i] = 1;
	for(int i = 1; i <= n; i++)
	{
		int u = top[i];
		for(int j = h[u]; ~j; j = ne[j])
		{
			int v = e[j];
			dp[v] = max(dp[v], dp[u] + 1);
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%d\n", dp[i]);
	return 0;
}
