#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10000, M = N << 1;
int n, m;
int k[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
ll f[N][3];
void dfs(int p, int fa)
{
	f[p][1] = k[p];
	bool flag = false;
	ll minn = 0x3f3f3f3f3f3f3f3f;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		dfs(e[i], p);
		if(f[e[i]][0] < f[e[i]][1])f[p][0] += f[e[i]][0], minn = min(minn, f[e[i]][1] - f[e[i]][0]);
		else f[p][0] += f[e[i]][1], flag = true;
		f[p][1] += min(f[e[i]][0], min(f[e[i]][1], f[e[i]][2]));
		f[p][2] += min(f[e[i]][0], f[e[i]][1]);
	}
	if(!flag)f[p][0] += minn;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		scanf("%d", &k[x]);
		scanf("%d", &m);
		while(m--)
		{
			int y;
			scanf("%d", &y);
			add(x, y), add(y, x);
		}
	}
	dfs(1, 0);
	printf("%lld\n", min(f[1][1], f[1][0]));
	return 0;
}