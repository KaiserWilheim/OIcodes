#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3010;
int n;
char a[N], b[N], c[N];
int na, nb, nc;
ll f[N][N], g[3][N], h[3][N], to;
int gc(int id)
{
	if(id <= na)return a[id];
	else if(id <= na + nb)return b[id - na];
	return c[id - na - nb];
}
int led(int k) { return (k > 0 ? na : 0) + (k > 1 ? nb : 0) + (k > 2 ? nc : 0) + 1; }
int red(int k) { return (k >= 0 ? na : 0) + (k >= 1 ? nb : 0) + (k >= 2 ? nc : 0); }
void solve()
{
	scanf("%s", a + 1);
	scanf("%s", b + 1);
	scanf("%s", c + 1);
	na = strlen(a + 1), nb = strlen(b + 1), nc = strlen(c + 1);
	n = na + nb + nc;
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	memset(h, 0, sizeof(h));
	to = 0;
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = n; j > i; j--)
		{
			if(gc(i) != gc(j))continue;
			int beli = (i > na) + (i > na + nb);
			int belj = (j > na) + (j > na + nb);
			if(beli == 0 && belj == 2)f[i][j] = 1;
			f[i][j] += g[belj][i];
			f[i][j] += h[beli][j];
			if(beli == 1 && belj == 1)f[i][j] += to;
			if(i != led(beli) && j != red(belj))
				f[i][j] += f[i - 1][j + 1];
			if(beli == 0 && belj == 2)to += f[i][j];
			if(belj != 0 && i != red(beli))g[belj - 1][i + 1] += f[i][j];
			if(beli != 2 && j != led(belj))h[beli + 1][j - 1] += f[i][j];
			if(f[i][j])
			{
				if(beli == belj)ans += (j - i <= 2) * f[i][j];
				if(beli + 1 == belj)ans += (1 + (i != red(beli)) + (j != led(belj))) * f[i][j];
			}
		}
	}
	ans += to * nb;
	printf("%lld\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
