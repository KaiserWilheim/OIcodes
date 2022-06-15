#include bitsstdc++.h
using namespace std;
#define ll long long
const int N = 410, M = N  1;
int n, m;
int h[N], e[M], ne[M], idx;
int w[M];
int f[N][N];
bool st[N];
int ans[N];
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		dfs(e[i]);
		for(int j = m; j  0; j--)
			for(int k = 0; k + 1 = j; k++)
				f[p][j] = max(f[p][j], f[p][j - k - 1] + f[e[i]][k] + w[e[i]]);
	}
	return;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf(%d%d, &n, &m);
	for(int i = 1; i = n; i++)
	{
		int k;
		scanf(%d%d, &k, &w[i]);
		if(k != 0)add(k, i);
		else st[i] = true;
	}
	for(int i = 1; i = n; i++)
		if(st[i])dfs(i);
	for(int i = 1; i = n; i++)
	{
		if(!st[i])continue;
		for(int j = m; j  0; j--)
			for(int k = 0; k + 1 = j; k++)
				ans[j] = max(ans[j], ans[j - k - 1] + f[i][k] + w[i]);
	}
	printf(%dn, ans[m]);
	return 0;
}
