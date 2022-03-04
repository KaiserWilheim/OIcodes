#include<bits/stdc++.h>
using namespace std;
const int N = 210, M = 6010;
int n, m, week;
struct Edge
{
	int a, b, w, id;
	bool operator < (const Edge &a) const
	{
		return w < a.w;
	}
}e[M], t[M];
bool vis[M];
int ans[M];
int p[N];
int find(int x)
{
	if(p[x] != x)
	{
		p[x] = find(p[x]);
	}
	return p[x];
}
void endtag()
{
	for(int i = 1; i <= week; i++)
	{
		printf("%d\n", ans[i]);
	}
	exit(0);
	return;
}
int main()
{
	cin >> n >> m;
	week = m;
	for(int i = 1; i <= m; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		e[i] = { a,b,w,i };
	}
	int res = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= m; i++)t[i] = e[i];
	sort(t + 1, t + m + 1);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int a = t[i].a, b = t[i].b, w = t[i].w, id = t[i].id;
		int pa = find(a), pb = find(b);
		if(pa != pb)
		{
			p[pa] = pb;
			res += w;
			vis[id] = true;
		}
	}
	int flag = 0;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)flag++;
	}
	if(flag > 1)
	{
		for(int i = 1; i <= m; i++)ans[i] = -1;
		endtag();
	}
	ans[m] = res;
	while(m--)
	{
		if(vis[m + 1])
		{
			res = 0;
			memset(vis, 0, sizeof(vis));
			for(int i = 1; i <= m; i++)t[i] = e[i];
			sort(t + 1, t + m + 1);
			for(int i = 1; i <= n; i++)p[i] = i;
			for(int i = 1; i <= m; i++)
			{
				int a = t[i].a, b = t[i].b, w = t[i].w, id = t[i].id;
				int pa = find(a), pb = find(b);
				if(pa != pb)
				{
					p[pa] = pb;
					res += w;
					vis[id] = true;
				}
			}
			int flag = 0;
			for(int i = 1; i <= n; i++)
			{
				if(p[i] == i)flag++;
			}
			if(flag > 1)
			{
				for(int i = 1; i <= m; i++)ans[i] = -1;
				endtag();
			}
			ans[m] = res;
		}
		else
		{
			ans[m] = ans[m + 1];
		}
	}
	endtag();
	return 0;
}
