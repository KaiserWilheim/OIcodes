#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int col[N];
void dfs(int p, int fa)
{
	col[p] = col[fa] ^ 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
	}
}
int ans[N];
bool vis[N];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	queue<int>schw, weis;
	for(int i = 1; i <= n; i++)
	{
		if(col[i])schw.push(i);
		else weis.push(i);
	}
	if(weis.size() <= n / 3)
	{
		for(int i = 3; i <= n; i += 3)
		{
			if(weis.empty())break;
			vis[i] = true;
			ans[weis.front()] = i;
			weis.pop();
		}
		for(int i = 1; i <= n; i++)
		{
			if(vis[i])continue;
			vis[i] = true;
			ans[schw.front()] = i;
			schw.pop();
		}
	}
	else if(schw.size() <= n / 3)
	{
		for(int i = 3; i <= n; i += 3)
		{
			if(schw.empty())break;
			vis[i] = true;
			ans[schw.front()] = i;
			schw.pop();
		}
		for(int i = 1; i <= n; i++)
		{
			if(vis[i])continue;
			vis[i] = true;
			ans[weis.front()] = i;
			weis.pop();
		}
	}
	else
	{
		for(int i = 1; i <= n; i += 3)
		{
			vis[i] = true;
			ans[schw.front()] = i;
			schw.pop();
		}
		for(int i = 2; i <= n; i += 3)
		{
			vis[i] = true;
			ans[weis.front()] = i;
			weis.pop();
		}
		for(int i = 3; i <= n; i += 3)
		{
			if(!weis.empty())
			{
				ans[weis.front()] = i;
				weis.pop();
			}
			else
			{
				ans[schw.front()] = i;
				schw.pop();
			}
			vis[i] = true;
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}
