#include<bits/stdc++.h>
using namespace std;
#define r register
const int N = 110, M = 40;
int n, c;
int w[N], v[N];
vector<pair<int, int> >h[M];
int f[M][N * M];
int g[M][N * M];
inline int lowbit(int x)
{
	return x & -x;
}
void init()
{
	memset(w, 0, sizeof(w));
	memset(v, 0, sizeof(v));
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	for(int i = 0; i < M; i++)h[i].clear();
}
int main()
{
	scanf("%d%d", &n, &c);
	while(n != -1 && c != -1)
	{
		init();
		for(r int i = 1; i <= n; i++)
		{
			scanf("%d%d", &w[i], &v[i]);
			r int b = log2(lowbit(w[i]));
			h[b].push_back(make_pair(w[i] >> b, v[i]));
		}
		r int cnt = log2(c);
		for(r int t = 0; t <= cnt; t++)
			for(r int i = 0; i < h[t].size(); i++)
				for(r int j = 10 * h[t].size(); j >= h[t][i].first; j--)
					f[t][j] = max(f[t][j], f[t][j - h[t][i].first] + h[t][i].second);
		for(r int i = 0; i <= 10 * h[0].size(); i++)
			g[0][i] = f[0][i];
		for(r int t = 1; t <= cnt; t++)
			for(r int j = 0; j <= 10 * n; j++)
				for(r int i = 0; i <= j; i++)
					g[t][j] = max(g[t][j], f[t][j - i] + g[t - 1][min(10 * n, i * 2 + ((c >> (t - 1)) & 1))]);
		printf("%d\n", g[cnt][1]);
		scanf("%d%d", &n, &c);
	}
	return 0;
}
