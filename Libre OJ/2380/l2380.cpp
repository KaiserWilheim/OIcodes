#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = 100010;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int D[4], st = 1, range;
int pos[N][4];
int ans;
bool use[N];
int vis[N], to[N], lim;

bool dfs(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(!use[w[i]] && vis[e[i]] < lim)
		{
			vis[e[i]] = lim;
			if(!to[e[i]] || dfs(to[e[i]]))
			{
				to[e[i]] = p;
				return true;
			}
		}
	}
	return false;
}
int getAns(int now)
{
	int res = 0;
	memset(to, 0, sizeof(to));
	for(int i = 1; i <= range; i++)
	{
		lim++;
		if(dfs(i))res++;
		if(now + res >= ans)return now + res;
	}
	return now + res;
}
void getState(int dep, int now)
{
	if(dep > D[st])
	{
		ans = min(ans, getAns(now));
		return;
	}
	use[dep] = 1;
	getState(dep + 1, now + 1);
	use[dep] = 0;
	getState(dep + 1, now);
}

void solve()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d%d", &D[1], &D[2], &D[3]);
	range = max(D[2], D[3]);
	if(D[2] < D[st])st = 2, range = max(D[1], D[3]);
	if(D[3] < D[st])st = 3, range = max(D[1], D[2]);
	for(int i = 1; i <= D[1]; i++)
	{
		for(int j = 1; j <= D[2]; j++)
		{
			for(int k = 1; k <= D[3]; k++)
			{
				int x;
				scanf("%d", &x);
				if(x)
				{
					n++;
					pos[n][1] = i;
					pos[n][2] = j;
					pos[n][3] = k;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(st == 1)add(pos[i][2], pos[i][3], pos[i][1]);
		if(st == 2)add(pos[i][1], pos[i][3], pos[i][2]);
		if(st == 3)add(pos[i][1], pos[i][2], pos[i][3]);
	}
	getState(1, 0);
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		idx = 0;
		st = 1;
		n = 0;
		ans = 0x3f3f3f3f;
		solve();
	}
	return 0;
}