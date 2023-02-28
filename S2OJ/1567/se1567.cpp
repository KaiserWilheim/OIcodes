#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010, M = (1 << 10) + 10, K = 110;
int n, m;
int a[N];
int f[2][M][K][6][2];
bool vis[M];
int to[M][6][6];
int val(int S, int i) { return (S >> (i << 1)) & 3; }
void init()
{
	memset(to, -1, sizeof(to));
	queue<int>q;
	vis[0] = true, q.push(0);
	while(!q.empty())
	{
		int S = q.front();
		q.pop();
		if(!vis[S])continue;
		for(int i = 1; i < 5; i++)
		{
			if(val(S, i) == 0 && !vis[S + (1 << (i * 2))])
			{
				vis[S + (1 << (i * 2))] = true;
				q.push(S + (1 << (i * 2)));
			}
		}
		for(int i = 0; i <= 5; i++)
		{
			for(int j = i + 1; j <= 5; j++)
			{
				bool flag = (val(S, i) <= 1);
				for(int k = i + 1; k < j; k++)flag &= !val(S, k);
				if(!flag)continue;
				int T = S + ((2 - val(S, i)) << (i * 2));
				for(int k = i + 1; k < j; k++)T |= 3 << (k << 1);
				to[S][i][j] = T;
				if(!vis[T])vis[T] = true, q.push(T);
			}
		}
	}
}
int main()
{
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memset(f, -63, sizeof(f));
	int o = 0;
	for(int i = 1; i < 5; i++)f[o][1 << (i * 2)][1][i][0] = 0;
	f[o][0][1][0][0] = f[o][0][1][5][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		o ^= 1;
		for(int S = 0; S < (1 << 10); S++)
			if(vis[S])memset(f[o][S], -63, sizeof(f[o][S]));
		for(int S = 0; S < (1 << 10); S++)
		{
			if(!vis[S])continue;
			for(int j = 1; j <= min(i, m); j++)
			{
				for(int k = 0; k <= 5; k++)
				{
					for(int ty = 0; ty < 2; ty++)
					{
						if(f[o ^ 1][S][j][k][ty] >= 0)
						{
							f[o][S][j][k][ty] = max(f[o][S][j][k][ty], f[o ^ 1][S][j][k][ty] + (a[i] == k));
							if(val(S, a[i]) != 3)
							{
								if(a[i] > 0 && a[i] < 5 && !val(S, a[i]))f[o][S | (1 << (a[i] * 2))][j + 1][a[i]][0] = max(f[o][S | (1 << (a[i] * 2))][j + 1][a[i]][0], f[o ^ 1][S][j][k][ty] + 1);
								else f[o][S][j + 1][a[i]][0] = max(f[o][S][j + 1][a[i]][0], f[o ^ 1][S][j][k][ty] + 1);
							}
							if(~to[S][k][a[i]])
							{
								if(ty && val(S, k))continue;
								f[o][to[S][k][a[i]] + ty * (1 << (k * 2))][j][a[i]][1] = max(f[o][to[S][k][a[i]] + ty * (1 << (k * 2))][j][a[i]][1], f[o ^ 1][S][j][k][ty] + 1);
							}
						}
					}
				}
			}
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int ans = 0;
		for(int S = 0; S < (1 << 10); S++)
			for(int j = 0; j <= 5; j++)
				for(int ty = 0; ty < 2; ty++)
					ans = max(ans, f[o][S][i][j][ty]);
		printf("%d ", ans);
	}
	putchar('\n');
	return 0;
}
