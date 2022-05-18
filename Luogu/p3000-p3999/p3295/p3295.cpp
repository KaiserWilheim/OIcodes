#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int mod = 1e9 + 7;
int n, m;
int p[N][20];
int find(int x, int i)
{
	if(p[x][i] != x)p[x][i] = find(p[x][i], i);
	return p[x][i];
}
void unite(int i, int j, int k)
{
	int pa = find(i, k), pb = find(j, k);
	if(pa != pb)p[pa][k] = pb;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 20; j++)
			p[i][j] = i;
	for(int i = 1, l1, r1, l2, r2; i <= m; i++)
	{
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		for(int k = 19; ~k; k--)
			if(l1 + (1 << k) - 1 <= r1)
			{
				unite(l1, l2, k);
				l1 += 1 << k, l2 += 1 << k;
			}
	}
	for(int i = 19; i; i--)
	{
		for(int j = 1; j + (1 << i) < n; j++)
		{
			int k = find(j, i);
			unite(j, k, i - 1);
			unite(j + (1 << (i - 1)), k + (1 << (i - 1)), i - 1);
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i)
		if(p[i][0] == i)
			ans = !ans ? 9 : ans * 10ll % mod;
	printf("%lld\n", ans);
	return 0;
}
