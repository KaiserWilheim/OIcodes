#include<bits/stdc++.h>
using namespace std;
const int N = 1010, M = 200010, INF = 1e8;
const int X[4] = { 0,0,1,-1 };
const int Y[4] = { 1,-1,0,0 };

int n, ans = 0, st, ed;

int h[N], e[M], ne[M], c[M], idx = 1;
void add(int a, int b, int v)
{
	e[++idx] = b, c[idx] = v, ne[idx] = h[a], h[a] = idx;
}

int num[N];
queue<int> q;
bool bfs()
{
	memset(num, 0, sizeof(num));
	num[st] = 1;
	q.push(st);
	while(!q.empty())
	{
		int x = q.front();
		for(int i = h[x]; ~i; i = ne[i])
		{
			int y = e[i];
			if(c[i] > 0 && num[y] == 0)
			{
				num[y] = num[x] + 1;
				q.push(y);
			}
		}
		q.pop();
	}
	if(num[ed]) return true;
	else return false;
}

int dfs(int x, int q)
{
	int s = 0, t;
	if(x == ed) return q;
	for(int i = h[x]; i; i = ne[i])
	{
		int y = e[i];
		if(c[i] && num[y] == num[x] + 1 && q > s)
		{
			s += (t = (dfs(y, min(q - s, c[i]))));
			c[i] -= t;
			c[i ^ 1] += t;
		}
	}
	if(!s) num[x] = 0;
	return s;
}

int dinic()
{
	int sum = 0;
	while(bfs())
		sum += dfs(st, INF);
	return sum;
}

bool chq(int t1, int t2)
{
	if(t1 <= 0)return false;
	if(t1 > n)return false;
	if(t2 <= 0)return false;
	if(t2 > n)return false;
	return true;
}
int main()
{
	int x, id;
	scanf("%d", &n);
	st = 0, ed = n * n + 1;
	memset(h, -1, sizeof(h));
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &x);
			ans += x;
			id = (i - 1) * n + j;
			if((i + j) & 1)
			{
				add(st, id, x);
				add(id, st, 0);
			}
			else
			{
				add(id, ed, x);
				add(ed, id, 0);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if((i + j) & 1)
			{
				for(int k = 0; k <= 3; k++)
				{
					int t1 = i + X[k], t2 = j + Y[k];
					if(!chq(t1, t2)) continue;
					id = (i - 1) * n + j;
					add(id, (t1 - 1) * n + t2, INF);
					add((t1 - 1) * n + t2, id, 0);
				}
			}
		}
	}
	printf("%d", ans - dinic());
	return 0;
}
