#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
const int N = 1010, M = N << 1;
int prime[N];
bool vis[N];
void seive(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!vis[i])prime[++prime[0]] = i;
		for(int j = 1; j <= prime[0] && i * prime[j] <= n; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
int n, m, k;
int h[N], e[M], ne[M], idx;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int rt, lrt;
int sz[N], msiz[N], minn;
void getrt(int p, int fa)
{
	sz[p] = 1, msiz[p] = 0;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		getrt(e[i], p);
		sz[p] += sz[e[i]];
		msiz[p] = max(msiz[p], sz[e[i]]);
	}
	msiz[p] = max(msiz[p], n - sz[p]);
	if(msiz[p] < minn && p != lrt)rt = p, minn = msiz[p];
}
ull geth(int p, int fa)
{
	ull res = 1;
	sz[p] = 1;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		res += geth(e[i], p) * prime[sz[e[i]]];
		sz[p] += sz[e[i]];
	}
	return res;
}
map<pair<ull, int>, int>bib;
int main()
{
	scanf("%d", &k);
	seive(1000);
	for(int _i = 1; _i <= k; _i++)
	{
		memset(h, -1, sizeof(h));
		idx = 0;
		scanf("%d", &n);
		lrt = rt = 0, minn = 1e9;
		for(int i = 1; i <= n; i++)
		{
			int fa;
			scanf("%d", &fa);
			if(fa)add(fa, i), add(i, fa);
			else rt = i;
		}
		getrt(rt, 0);
		lrt = rt, minn = 1e9;
		getrt(lrt, 0);
		ull res = min(geth(rt, 0), geth(lrt, 0));
		if(!bib.count(make_pair(res, n)))bib[make_pair(res, n)] = _i;
		printf("%d\n", bib[make_pair(res, n)]);
	}
	return 0;
}
