#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m, q;
int cnt;
int fa[N][20];
int id[N], pos[N];
vector<int>cyc[N];

int chq(int x, int y)
{
	if(x == 1)return 1;
	ll res = 1;
	while(y--)
	{
		res *= x;
		if(res > n)return -1;
	}
	return res;
}
int jump(int p, int x)
{
	int i = 0;
	while(x)
	{
		if(x & 1)p = fa[p][i];
		i++;
		x >>= 1;
	}
	return p;
}
int qpow(int a, int x, int mod)
{
	ll res = 1;
	while(x)
	{
		if(x & 1)res = (res * 1ll * a) % mod;
		a = (1ll * a * a) % mod;
		x >>= 1;
	}
	return res;
}
int main()
{
	scanf("%d", &n);
	cnt = log(n) / log(2) + 1e-7;
	for(int i = 1; i <= n; i++)
		scanf("%d", &fa[i][0]);
	for(int j = 1; j <= cnt; j++)
		for(int i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	for(int i = 1; i <= n; i++)
	{
		int u = fa[fa[i][cnt]][cnt];
		if(!id[u])
		{
			++m;
			for(; !id[u]; u = fa[u][0])
			{
				id[u] = m;
				pos[u] = cyc[m].size();
				cyc[m].push_back(u);
			}
		}
	}
	scanf("%d", &q);
	while(q--)
	{
		int p, x, y;
		scanf("%d%d%d", &p, &x, &y);
		int z = chq(x, y);
		if(z == -1)
		{
			p = jump(p, n);
			int sz = cyc[id[p]].size();
			z = (qpow(x, y, sz) + sz - n % sz) % sz;
			p = cyc[id[p]][(pos[p] + z) % sz];
		}
		else p = jump(p, z);
		printf("%d\n", p);
	}
	return 0;
}
