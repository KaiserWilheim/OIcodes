#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int K = 60, N = 10010, M = N << 3;
const int INF = 1e9;
int n, m, k;
int S, T;
int h[N], e[M], ne[M], idx;
int f[M], w[M];
void add(int a, int b, int c, int d)
{
	e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}
int d[N], pre[N], incf[N];
bool st[N];
bool spfa()
{
	queue<int>q;
	memset(d, 63, sizeof(d));
	memset(incf, 0, sizeof(incf));
	d[S] = 0, incf[S] = INF;
	q.push(S);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		st[u] = false;
		for(int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if(f[i] && d[v] > d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				pre[v] = i;
				incf[v] = min(f[i], incf[u]);
				if(!st[v])
				{
					q.push(v);
					st[v] = true;
				}
			}
		}
	}
	return incf[T] > 0;
}
void EK(int &flow, int &cost)
{
	flow = cost = 0;
	while(spfa() && d[T] < 0)
	{
		int t = incf[T];
		flow += t, cost += t * d[T];
		for(int i = T; i != S; i = e[pre[i] ^ 1])
		{
			f[pre[i]] -= t;
			f[pre[i] ^ 1] += t;
		}
	}
}
int cnt;
int id[K][K];
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &n, &m, &k);
	S = 0, T = ++cnt;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			id[i][j] = ++cnt;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			add(S, id[i][j], 1, 0);
	for(int i = 1; i <= k; i++)
	{
		int x, y;
		char op[5];
		scanf("%d%d%s", &x, &y, op);
		x++, y++;
		int nx = x + (op[0] == 'D') - (op[0] == 'U');
		int ny = y + (op[0] == 'R') - (op[0] == 'L');
		int pre = id[nx][ny];
		cnt++; id[nx][ny] = ++cnt;
		add(pre, cnt - 1, 1, 0);
		add(cnt - 1, cnt, 1, 0);
		add(id[x][y], cnt - 1, 1, -1);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			add(id[i][j], T, 1, 0);
	int flow, cost;
	EK(flow, cost);
	printf("%d\n", k + cost);
	return 0;
}
