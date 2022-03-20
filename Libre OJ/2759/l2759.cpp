#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100005;
const int M = 300005;
int head[N], ne[M << 1], to[M << 1], cost[M << 1], idx;
#define add(a,b,c) to[++idx]=b,ne[idx]=head[a],head[a]=idx,cost[idx]=c
#define bianli(x) for(int i=head[x];i;i=ne[i])
int val[N];
int n, m;
ll sum[N];
int H[N];
bool mark[N];
struct node
{
	ll v;
	int id;
	bool operator <(const node &A)const
	{
		return v > A.v;
	}
};
priority_queue<node> q;
void dijkstra(int at)
{
	for(int i=1;i<=n;i++)sum[i]=1e18;
	q.push({ 0,1 });
	H[1] = at;
	sum[1] = 0;
	ll v;
	while(!q.empty())
	{
		node now = q.top();
		q.pop();
		if(mark[now.id])continue;
		mark[now.id] = 1;
		int h = H[now.id];
		bianli(now.id)
		{
			if(h - cost[i] > val[to[i]])
			{
				v = sum[now.id] + h - cost[i] - val[to[i]] + cost[i];
				if(sum[to[i]] > v)
				{
					sum[to[i]] = v;
					H[to[i]] = val[to[i]];
					q.push({ sum[to[i]],to[i] });
				}
			}
			else if(h - cost[i] < 0)
			{
				v = sum[now.id] + cost[i] - h + cost[i];
				if(sum[to[i]] > v)
				{
					sum[to[i]] = v;
					H[to[i]] = 0;
					q.push({ sum[to[i]],to[i] });
				}
			}
			else
			{
				if(sum[to[i]] > sum[now.id] + cost[i])
				{
					sum[to[i]] = sum[now.id] + cost[i];
					H[to[i]] = h - cost[i];
					q.push({ sum[to[i]],to[i] });
				}
			}
		}
	}
}
int main()
{
	int at;
	scanf("%d%d%d", &n, &m, &at);
	for(int i = 1; i <= n; i++)scanf("%d", &val[i]);
	int a, b, c;
	while(m--)
	{
		scanf("%d%d%d", &a, &b, &c);
		if(val[a] >= c)add(a, b, c);
		if(val[b] >= c)add(b, a, c);
	}
	dijkstra(at);
	if(sum[n] == 1e18)puts("-1");
	else printf("%lld\n", sum[n] + val[n] - H[n]);
	return 0;
}
