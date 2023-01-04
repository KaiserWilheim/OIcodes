#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 4000010;
struct List
{
	int pr, ne;
};
int n, m;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
bool vis[N], cov[N];
int sz[N], sc;
List re[N];
void del(int x)
{
	re[re[x].ne].pr = re[x].pr;
	re[re[x].pr].ne = re[x].ne;
}
void bfs(int s)
{
	vis[s] = true;
	sz[++sc] = 0;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = h[p]; ~i; i = ne[i])
			if(!vis[e[i]])
				cov[e[i]] = true;
		for(int i = re[0].ne; i != -1; i = re[i].ne)
		{
			if(!cov[i])
			{
				vis[i] = true;
				sz[sc]++;
				del(i);
				q.push(i);
			}
			else cov[i] = false;
		}
	}
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	re[0] = { -1,1 };
	for(int i = 1; i <= n; i++)
		re[i] = { i - 1,i + 1 };
	re[n].ne = -1;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++)
		if(!vis[i])bfs(i);
	sort(sz + 1, sz + 1 + sc);
	printf("%d\n", sc);
	for(int i = 1; i <= sc; i++)
		printf("%d ", sz[i]);
	putchar('\n');
	return 0;
}