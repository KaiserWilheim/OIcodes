#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = N << 1;
int n, m;
struct Edge
{
	int u, v;
	ll w;
	bool operator < (const Edge &rhs) const
	{
		return w < rhs.w;
	}
};
Edge e[M];
int nd[N], hv[N];
bool f[N], vld[N];
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
bool chq(int S)
{
	vector<Edge>v;
	for(int i = 1; i <= m; i++)
		if((S >> (e[i].u - 1) & 1) && (S >> (e[i].v - 1) & 1))
			v.push_back(e[i]);
	sort(v.begin(), v.end());
	for(int i = 1; i <= n; i++)p[i] = i;
	ll sum = 0;
	for(int i = 1; i <= n; i++)
		if(S >> (i - 1) & 1)
			sum += hv[i] - nd[i];
	for(auto i : v)
	{
		int u = find(i.u), v = find(i.v);
		if(u != v)
		{
			p[u] = v;
			sum -= i.w;
		}
	}
	int rt = 0;
	for(int i = 1; i <= n; i++)
		if(S >> (i - 1) & 1)
			if(find(i) == i) { rt = i; break; }
	for(int i = 1; i <= n; i++)
		if(S >> (i - 1) & 1)
			if(find(i) != rt)return false;
	return sum >= 0;
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
		e[i] = { u,v,w };
	}
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &hv[i], &nd[i]);
	for(int S = 1; S < (1 << n); S++)
		f[S] = false, vld[S] = chq(S);
	f[0] = true;
	for(int S = 1; S < (1 << n); S++)
		for(int T = S; T; T = (T - 1) & S)
			if(vld[T] && f[S ^ T])f[S] = true;
	if(f[(1 << n) - 1])puts("Yes");
	else puts("No");
	return;
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