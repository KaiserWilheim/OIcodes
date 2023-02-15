#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110, M = 2010;
int n, m, k;
struct Node
{
	int a, b, t;
	bool operator < (const Node &rhs)const { return a < rhs.a; }
};
Node a[N];
int dis(int i, int j) { return abs(a[i].a - a[j].a); }
int f[N][N][M][2];
int main()
{
	int maxt = 0;
	scanf("%d%d%d", &n, &k, &m);
	bool flag = false;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].t);
		if(a[i].a == k)flag = true;
		maxt = max(maxt, a[i].t);
	}
	if(!flag)a[++m] = { k,0,0 };
	sort(a + 1, a + 1 + m);
	int st = -1;
	for(int i = 1; i <= m; i++)
		if(a[i].a == k)st = i;
	int ans = 0;
	memset(f, -63, sizeof(f));
	f[st][st][0][0] = f[st][st][0][1] = a[st].b;
	for(int i = st + 1; i <= m; i++)
	{
		f[st][i][dis(st, i)][1] = f[st][i - 1][dis(st, i - 1)][1] + (dis(st, i) < a[i].t ? a[i].b : 0);
		ans = max(ans, f[st][i][dis(st, i)][1]);
	}
	for(int i = st - 1; i; i--)
	{
		f[i][st][dis(i, st)][0] = f[i + 1][st][dis(i + 1, st)][0] + (dis(st, i) < a[i].t ? a[i].b : 0);
		ans = max(ans, f[i][st][dis(st, i)][0]);
	}
	for(int t = 1; t <= maxt; t++)
	{
		for(int l = st - 1; l >= 1; l--)
		{
			for(int r = st + 1; r <= m; r++)
			{
				f[l][r][t][0] = max(f[l + 1][r][max(t - dis(l, l + 1), 0)][0], f[l + 1][r][max(t - dis(l, r), 0)][1]) + (t < a[l].t ? a[l].b : 0);
				f[l][r][t][1] = max(f[l][r - 1][max(t - dis(r, r - 1), 0)][1], f[l][r - 1][max(t - dis(l, r), 0)][0]) + (t < a[r].t ? a[r].b : 0);
				ans = max(ans, max(f[l][r][t][0], f[l][r][t][1]));
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
