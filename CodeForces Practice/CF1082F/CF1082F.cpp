#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int n, k;
struct Trie
{
	int s[10];
	int w;
};
Trie tr[N];
int idx;
char s[N];
int len;
void insert(int v)
{
	int p = 0;
	for(int i = 1; i <= len; i++)
	{
		int c = s[i] - '0';
		if(!tr[p].s[c])tr[p].s[c] = ++idx;
		p = tr[p].s[c];
	}
	tr[p].w += v;
}
int f[N][N][12];
void dfs(int p, int dep)
{
	for(int c = 0; c < 10; c++)
		if(tr[p].s[c])dfs(tr[p].s[c], dep + 1);
	for(int i = 0; i <= dep; i++)
		for(int j = 0; j <= k; j++)
			f[p][i][j] = i * tr[p].w;
	for(int c = 0; c < 10; c++)
	{
		if(!tr[p].s[c])continue;
		int v = tr[p].s[c];
		for(int i = 0; i <= dep; i++)
		{
			for(int j = k; j >= 0; j--)
			{
				f[p][i][j] += f[v][i + 1][0];
				for(int x = 1; x <= j; x++)
				{
					f[p][i][j] = min(f[p][i][j], f[p][i][j - x] + f[v][i + 1][x]);
					f[p][i][j] = min(f[p][i][j], f[p][i][j - x] + f[v][0][x - 1]);
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int m;
		scanf("%s%d", s + 1, &m);
		len = strlen(s + 1);
		insert(m);
	}
	dfs(0, 0);
	printf("%d\n", f[0][0][k]);
	return 0;
}
