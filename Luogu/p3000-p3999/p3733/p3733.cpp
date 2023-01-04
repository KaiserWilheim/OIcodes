#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define bs bitset<N>
const int N = 1010, M = N << 1;
const int INF = 1e9;
int n, m, q;
int h[N], e[M], ne[M], idx;
bs w[M];
void add(int a, int b, bs c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void print(bs &x)
{
	bool flag = false;
	for(int i = 999; i >= 0; i--)
	{
		if(x[i] || flag)putchar('0' + x[i]);
		if(x[i])flag = true;
	}
	if(!flag)putchar('0');
	putchar('\n');
}
bs d[N], dis[N];
int tms[N];
void insert(int now, bs x)
{
	for(int i = 1000; i >= 0; i--)
	{
		if(!x[i])continue;
		if(tms[i] < now)swap(tms[i], now), swap(d[i], x);
		if(!now)break;
		x ^= d[i];
	}
}
bool vis[N];
void dfs(int p)
{
	for(int i = h[p]; ~i; i = ne[i])
	{
		if(vis[e[i]])insert(INF, dis[p] ^ dis[e[i]] ^ w[i]);
		else
		{
			vis[e[i]] = true;
			dis[e[i]] = dis[p] ^ w[i];
			dfs(e[i]);
		}
	}
}
void query(int now)
{
	bs res;
	for(int i = 1000; i >= 0; i--)
		if(tms[i] > now && !res[i])res ^= d[i];
	print(res);
}
int op[N], pos[N], ed[N], tot, tag;
bs aft[N];
pair<int, int>nw[N];
int main()
{
	memset(h, -1, sizeof(h));
	cin >> n >> m >> q;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		string w;
		cin >> u >> v >> w;
		add(u, v, bs(w)), add(v, u, bs(w));
	}
	dfs(1);
	query(0);
	tag = q + 1;
	for(int i = 1; i <= q; i++)
	{
		string opt;
		cin >> opt;
		if(opt[1] == 'd')
		{
			int x, y;
			string z;
			cin >> x >> y >> z;
			op[i] = ++tot;
			aft[tot] = (bs(z) ^ dis[x] ^ dis[y]);
			nw[tot] = make_pair(x, y);
			pos[tot] = tot;
		}
		else if(opt[1] == 'h')
		{
			int x;
			string z;
			cin >> x >> z;
			ed[pos[x]] = i;
			op[i] = --tag;
			aft[tag] = (dis[nw[x].first] ^ dis[nw[x].second] ^ bs(z));
			pos[x] = tag;
		}
		else if(opt[1] == 'a')
		{
			int x;
			cin >> x;
			ed[pos[x]] = i;
		}
	}
	for(int i = 1; i <= q; i++)
		if(!ed[i])ed[i] = INF;
	for(int i = 1; i <= q; i++)
	{
		if(op[i])insert(ed[op[i]], aft[op[i]]);
		query(i);
	}
	return 0;
}
