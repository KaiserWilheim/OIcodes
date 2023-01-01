#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
int n, m;
int a[N], b[N];
struct Node
{
	int v, id;
	bool operator < (const Node &rhs)const
	{
		return v > rhs.v;
	}
};
struct Chart
{
	int v;
	int l, r;
};
Chart p[N];
void del(int x)
{
	p[x].l = p[p[x].l].l;
	p[x].r = p[p[x].r].r;
	p[p[x].l].r = x;
	p[p[x].r].l = x;
}
bool vis[N];
priority_queue<Node>q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	sort(b + 1, b + 1 + n);
	for(int i = 1; i < n; i++)
	{
		a[i] = b[i + 1] - b[i];
		p[i] = { a[i],i - 1,i + 1 };
	}
	p[0].v = p[n].v = 1e9;
	for(int i = 1; i < n; i++)
		q.push({ a[i],i });
	int ans = 0;
	for(int i = 1; i <= m; i++)
	{
		while(vis[q.top().id])q.pop();
		Node u = q.top();
		q.pop();
		ans += u.v;
		vis[p[u.id].l] = vis[p[u.id].r] = true;
		p[u.id].v = p[p[u.id].l].v + p[p[u.id].r].v - p[u.id].v;
		q.push({ p[u.id].v,u.id });
		del(u.id);
	}
	printf("%d\n", ans);
	return 0;
}