#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50010, M = 100010;
int n, m, t;
int mil[N];
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int fa[N][32];
ll dis[N][32];
void getFa(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p][0])continue;
		int j = e[i];
		fa[j][0] = p;
		dis[j][0] = w[i];
		getFa(j);
	}
}
void initFa()
{
	for(int p = 1; p <= n; p++)
	{
		for(int i = 1; i <= t; i++)
		{
			fa[p][i] = fa[fa[p][i - 1]][i - 1];
			dis[p][i] = dis[p][i - 1] + dis[fa[p][i - 1]][i - 1];
		}
	}
}
bool scr[N], need[N];
bool isScrd(int p)
{
	bool isLeaf = true;
	if(scr[p])return true;
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(e[i] == fa[p][0])continue;
		isLeaf = false;
		if(!isScrd(e[i]))return false;
	}
	if(isLeaf)return false;
	return true;
}
bool chq(ll lim)
{
	memset(scr, 0, sizeof(scr));
	memset(need, 0, sizeof(need));
	vector<pair<ll, int> >q;
	for(int i = 1; i <= m; i++)
	{
		int x = mil[i];
		ll cnt = 0;
		for(int j = t; j >= 0; j--)
		{
			if(fa[x][j] > 1 && cnt + dis[x][j] <= lim)
			{
				cnt += dis[x][j];
				x = fa[x][j];
			}
		}
		if(fa[x][0] == 1 && cnt + dis[x][0] <= lim)
			q.emplace_back(lim - cnt - dis[x][0], x);
		else scr[x] = true;
	}
	sort(q.begin(), q.end());
	vector<ll>rmtm;
	for(int i = h[1]; ~i; i = ne[i])
		if(!isScrd(e[i]))
			need[e[i]] = true;
	for(auto u = q.begin(); u != q.end(); u++)
	{
		if(need[u->second] && u->first < dis[u->second][0] * 2)need[u->second] = false;
		else rmtm.push_back(u->first);
	}
	vector<ll>tbd;
	for(int i = h[1]; ~i; i = ne[i])
		if(need[e[i]])tbd.push_back(dis[e[i]][0]);
	if(rmtm.size() < tbd.size())return false;
	sort(rmtm.begin(), rmtm.end());
	sort(tbd.begin(), tbd.end());
	vector<ll>::iterator i = tbd.begin(), j = rmtm.begin();
	while(i != tbd.end() && j != rmtm.end())
	{
		if(*i <= *j)i++, j++;
		else j++;
	}
	if(i == tbd.end())return true;
	else return false;
}
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	t = log2(n) + 1;
	ll l = 0, r = 0;
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w), add(v, u, w);
		r += w;
	}
	getFa(1);
	initFa();
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
		scanf("%d", &mil[i]);
	bool isValid = false;
	while(l < r)
	{
		ll mid = (l + r) >> 1;
		if(chq(mid))
		{
			r = mid;
			isValid = true;
		}
		else l = mid + 1;
	}
	if(!isValid)puts("-1");
	else printf("%lld\n", l);
	return 0;
}