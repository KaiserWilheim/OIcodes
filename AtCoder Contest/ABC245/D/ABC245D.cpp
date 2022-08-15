#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long
#define db double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 524288, mod = 998244353, G = 3, iG = (mod + 1) / G;
int qpow(int x, int y = mod - 2)
{
	int res = 1;
	for(; y; x = ( ll )x * x % mod, y >>= 1) if(y & 1) res = ( ll )res * x % mod;
	return res;
}
int lim, pp[N];
void revlim() { L(i, 0, lim - 1) pp[i] = ((pp[i >> 1] >> 1) | ((i & 1) * (lim >> 1))); }
void up(int x) { lim = 1; for(; lim <= x; lim <<= 1); }
void cle(int *f) { L(i, 0, lim - 1) f[i] = 0; }
void NTT(int *f, int flag)
{
	L(i, 0, lim - 1) if(pp[i] < i) swap(f[pp[i]], f[i]);
	for(int i = 2; i <= lim; i <<= 1)
		for(int j = 0, l = (i >> 1), ch = qpow(flag == 1 ? G : iG, (mod - 1) / i); j < lim; j += i)
			for(int k = j, now = 1; k < j + l; k++)
			{
				int pa = f[k], pb = ( ll )f[k + l] * now % mod;
				f[k] = (pa + pb) % mod, f[k + l] = (pa + mod - pb) % mod;
				now = ( ll )now * ch % mod;
			}
	if(flag == -1)
	{
		int nylim = qpow(lim);
		L(i, 0, lim - 1) f[i] = ( ll )f[i] * nylim % mod;
	}
}
int sav[N], sv[N];
void inv(int *f, int *g, int len)
{
	if(len == 1) return g[0] = qpow(f[0]), void();
	inv(f, g, (len + 1) >> 1), up(len << 1), cle(sav), copy(f, f + len, sav), revlim(), NTT(sav, 1), NTT(g, 1);
	L(i, 0, lim - 1) g[i] = ( ll )g[i] * (2ll + mod - ( ll )g[i] * sav[i] % mod) % mod;
	NTT(g, -1), fill(g + len, g + lim, 0);
}
int sava[N], savb[N];
void div(int *f, int *g, int *ansa, int *ansb, int n, int m)
{
	up(n << 1), cle(sava), cle(savb), copy(g, g + m, sava), reverse(sava, sava + m);
	inv(sava, savb, n), up(n << 1), revlim(), copy(f, f + n, sava), reverse(sava, sava + n);
	NTT(sava, 1), NTT(savb, 1);
	L(i, 0, lim - 1) ansa[i] = ( ll )sava[i] * savb[i] % mod;
	NTT(ansa, -1), fill(ansa + n - m + 1, ansa + lim, 0), reverse(ansa, ansa + n - m + 1);
	cle(sav), cle(sava), copy(ansa, ansa + n - m + 1, sav), copy(g, g + m, sava), NTT(sav, 1), NTT(sava, 1);
	L(i, 0, lim - 1) sav[i] = ( ll )sav[i] * sava[i] % mod;
	NTT(sav, -1);
	L(i, 0, m - 2) ansb[i] = (f[i] + mod - sav[i]) % mod;
}
int n, m, f[N], g[N], ansa[N], ansb[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	int temp = m;
	m = n + 1;
	n += temp + 1;
	L(i, 0, m - 1) cin >> g[i];
	L(i, 0, n - 1) cin >> f[i];
	div(f, g, ansa, ansb, n, m);
	L(i, 0, n - m)if(ansa[i] > 100)ansa[i] -= mod;
	L(i, 0, n - m) cout << ansa[i] << " ";
	cout << endl;
	return 0;
}
