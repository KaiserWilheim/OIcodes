#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int K = 25, N = K * K * 2, M = N << 3;
const int INF = 1e9;
int n, m;
int S, T;
char maps[K][K], mapt[K][K];
char cnt[K][K];
int h[N], e[M], ne[M], f[M], w[M], idx;
#define px(i,j) ((i-1)*m+(j))
#define py(i,j) ((i-1)*m+(j)+(n*m))
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
	while(spfa())
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
int dx[10] = { 1,1,0,-1,-1,-1,0,1 }, dy[10] = { 0,-1,-1,-1,0,1,1,1 };
bool chq(int x, int y)
{
	if(x < 1)return false;
	if(x > n)return false;
	if(y < 1)return false;
	if(y > m)return false;
	return true;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", maps[i] + 1);
	for(int i = 1; i <= n; i++)
		scanf("%s", mapt[i] + 1);
	for(int i = 1; i <= n; i++)
		scanf("%s", cnt[i] + 1);
	int tots = 0, tott = 0;
	S = 0, T = n * m * 2 + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(maps[i][j] == '1' && mapt[i][j] != '1')add(S, px(i, j), 1, 0), tots++;
			if(mapt[i][j] == '1' && maps[i][j] != '1')add(py(i, j), T, 1, 0), tott++;
			int val = (cnt[i][j] - '0') / 2;
			if((maps[i][j] ^ mapt[i][j]) && (cnt[i][j] & 1))val++;
			add(px(i, j), py(i, j), val, 0);
			for(int k = 0; k < 8; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				if(chq(nx, ny))add(py(i, j), px(nx, ny), INF, 1);
			}
		}
	}
	if(tots != tott)
	{
		puts("-1");
		return 0;
	}
	int flow, cost;
	EK(flow, cost);
	if(flow != tots)puts("-1");
	else printf("%d\n", cost);
	return 0;
}
