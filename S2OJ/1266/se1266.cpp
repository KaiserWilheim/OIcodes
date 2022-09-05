#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100005;
const int M = 300005;
int h[N], ne[M << 1], e[M << 1], w[M << 1], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int val[N];
int n, m;
ll sum[N];
int H[N];
bool mark[N];
struct node
{
	ll v;
	int id;
	bool operator < (const node &A)const
	{
		return v > A.v;
	}
};
priority_queue<node> q;
void dijkstra(int at)
{
	for(int i = 1; i <= n; i++)sum[i] = 1e18;
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
		int nh = H[now.id];
		for(int i = h[now.id]; ~i; i = ne[i])
		{
			if(nh - w[i] > val[e[i]])
			{
				v = sum[now.id] + nh - w[i] - val[e[i]] + w[i];
				if(sum[e[i]] > v)
				{
					sum[e[i]] = v;
					H[e[i]] = val[e[i]];
					q.push({ sum[e[i]],e[i] });
				}
			}
			else if(nh - w[i] < 0)
			{
				v = sum[now.id] + w[i] - nh + w[i];
				if(sum[e[i]] > v)
				{
					sum[e[i]] = v;
					H[e[i]] = 0;
					q.push({ sum[e[i]],e[i] });
				}
			}
			else
			{
				if(sum[e[i]] > sum[now.id] + w[i])
				{
					sum[e[i]] = sum[now.id] + w[i];
					H[e[i]] = nh - w[i];
					q.push({ sum[e[i]],e[i] });
				}
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
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