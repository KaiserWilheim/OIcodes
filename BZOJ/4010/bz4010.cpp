#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010, M = 1000010;
int n, m;
int h[N], e[M], ne[M], idx;
int deg[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
priority_queue<int>q;
int ans[N], tot;
void solve()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	bool isValid = false;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u == v)isValid = true;
		deg[u]++;
		add(v, u);
	}
	if(isValid)
	{
		puts("Impossible!");
		return;
	}
	for(int i = 1; i <= n; i++)
		if(!deg[i])q.push(i);
	while(!q.empty())
	{
		int u = q.top();
		q.pop();
		ans[++tot] = u;
		for(int i = h[u]; ~i; i = ne[i])
			if(!(--deg[e[i]]))q.push(e[i]);
	}
	if(tot < n)
	{
		puts("Impossible!");
		return;
	}
	for(int i = n; i; i--)
		printf("%d ", ans[i]);
	putchar('\n');
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(deg, 0, sizeof(deg));
		idx = 0;
		tot = 0;
		solve();
	}
	return 0;
}