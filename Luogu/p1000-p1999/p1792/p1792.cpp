#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int a[N];
struct Node
{
	int v, id;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		return lhs.v < rhs.v;
	}
};
struct Chart
{
	int v, l, r;
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
priority_queue<Node, vector<Node>>q;
int main()
{
	int pre;
	scanf("%d%d", &n, &m);
	if(n < m * 2)
	{
		puts("Error!");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		p[i] = { a[i],i - 1,i + 1 };
	}
	p[1].l = n, p[n].r = 1;
	for(int i = 1; i <= n; i++)
		q.push({ a[i],i });
	ll ans = 0;
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
	printf("%lld\n", ans);
	return 0;
}