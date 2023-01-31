#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 600010, M = N << 1;
const ll mod = 1e18;
int n;
ll w[N], s[N];
int pr[N], ne[N];
int col[N], fa[N][28];
int minn[N << 3];
void pushup(int p)
{
	minn[p] = min(minn[p << 1], minn[p << 1 | 1]);
}
void segchg(int p, int l, int r, int pos, int k)
{
	if(l == r)
	{
		minn[p] = k;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)segchg(p << 1, l, mid, pos, k);
	else segchg(p << 1 | 1, mid + 1, r, pos, k);
	pushup(p);
}
int segmin(int p, int l, int r, int ql, int qr)
{
	if(ql <= l && r <= qr)return minn[p];
	int mid = (l + r) >> 1;
	int res = 2e9;
	if(ql <= mid)res = min(res, segmin(p << 1, l, mid, ql, qr));
	if(qr > mid)res = min(res, segmin(p << 1 | 1, mid + 1, r, ql, qr));
	return res;
}
map<ll, int>bib;
ll sum;
void add(ll x, int k)
{
	bib[x] += k;
	sum += x * k;
}
ll sta[N], tt;
int update(int x)
{
	int res = 0; tt = 0;
	for(auto it = bib.upper_bound(x); it != bib.end(); it++)
	{
		sta[++tt] = it->first;
		res += it->second;
		sum -= it->first * it->second;
	}
	while(tt)bib.erase(sta[tt--]);
	return res;
}
ll ansh, ansl;
ll ans26, ansb;
void addans(ll x)
{
	ansl += x;
	if(ansl >= mod)ansl -= mod, ansh++;
	ans26 = (ans26 + x) % 26;
	ansb = (ansb + x) & ((1 << 30) - 1);
}
void print()
{
	if(ansh == 0)printf("%lld\n", ansl);
	else printf("%lld%018lld\n", ansh, ansl);
}
char c[5];
int main()
{
	scanf("%d", &n);
	scanf("%s%d", c, &w[1]);
	s[1] = c[0] - 'a';
	segchg(1, 1, n, 1, w[1]);
	addans(w[1]);
	print();
	for(int i = 2, j = 0; i <= n; i++)
	{
		scanf("%s%d", c, &w[i]);
		s[i] = (c[0] - 'a' + ans26) % 26;
		w[i] ^= ansb;
		if(s[1] == s[i])add(w[i], 1);
		segchg(1, 1, n, i, w[i]);
		addans(segmin(1, 1, n, 1, i));
		j = ne[i - 1];
		while(j && s[j + 1] != s[i])j = ne[j];
		ne[i] = j + (s[j + 1] == s[i]), col[i - 1] = s[i];
		for(int j = 0; j < 26; j++)fa[i][j] = fa[ne[i]][j];
		fa[i][col[ne[i]]] = ne[i];
		for(int c = 0; c < 26; c++)
		{
			if(c == s[i])continue;
			for(int j = fa[i - 1][c]; j; j = fa[j][c])
				add(segmin(1, 1, n, i - j, i - 1), -1);
		}
		add(w[i], update(w[i]));
		addans(sum);
		print();
	}
	return 0;
}
