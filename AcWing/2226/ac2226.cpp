#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 150010, M = N << 1;
int n, m, A;
int h[N], e[M], w[M], ne[M], idx;
int age[N];
bool st[N];
struct Father
{
	int u, num;
	ll dis;
};
vector<Father>f[N];
struct Son
{
	int age;
	ll dis;
	bool operator < (const Son &a) const
	{
		return age < a.age;
	}
};
vector<Son>son[N][3];

void add(int a, int b, int c)
{
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int get_sz(int u, int fa)
{
	if(st[u])return 0;
	int res = 1;
	for(int i = h[u]; ~i; i = ne[i])
		if(e[i] != fa)
			res += get_sz(e[i], u);
	return res;
}

int get_zx(int u, int fa, int tot, int &zx)
{
	if(st[u])return 0;
	int sum = 1, ms = 0;
	for(int i = h[u]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		int t = get_zx(e[i], u, tot, zx);
		ms = max(ms, t);
		sum += t;
	}
	ms = max(ms, tot - sum);
	if(ms <= tot / 2)zx = u;
	return sum;
}

void get_dis(int u, int fa, ll dis, int zx, int k, vector<Son> &p)
{
	if(st[u])return;
	f[u].push_back({ zx,k,dis });
	p.push_back({ age[u],dis });
	for(int i = h[u]; ~i; i = ne[i])
	{
		if(e[i] == fa)continue;
		get_dis(e[i], u, dis + w[i], zx, k, p);
	}
}

void calc(int u)
{
	if(st[u])return;
	get_zx(u, -1, get_sz(u, -1), u);
	st[u] = true;
	for(int i = h[u], k = 0; ~i; i = ne[i])
	{
		if(st[e[i]])continue;
		auto &p = son[u][k];
		p.push_back({ -1,0 });
		p.push_back({ A + 1,0 });
		get_dis(e[i], -1, w[i], u, k, p);
		k++;
		sort(p.begin(), p.end());
		for(int i = 1; i < p.size(); i++)
			p[i].dis += p[i - 1].dis;
	}
	for(int i = h[u]; ~i; i = ne[i])calc(e[i]);
}

ll query(int u, int l, int r)
{
	ll res = 0;
	for(auto &t : f[u])
	{
		int g = age[t.u];
		if((g >= l) && (g <= r))res += t.dis;
		for(int i = 0; i < 3; i++)
		{
			if(i == t.num)continue;
			auto &p = son[t.u][i];
			if(p.empty())continue;
			int a = lower_bound(p.begin(), p.end(), Son({ l,-1 })) - p.begin();
			int b = lower_bound(p.begin(), p.end(), Son({ r + 1,-1 })) - p.begin();
			res += t.dis * (b - a) + p[b - 1].dis - p[a - 1].dis;
		}
	}
	for(int i = 0; i < 3; i++)
	{
		auto &p = son[u][i];
		if(p.empty())continue;
		int a = lower_bound(p.begin(), p.end(), Son({ l,-1 })) - p.begin();
		int b = lower_bound(p.begin(), p.end(), Son({ r + 1,-1 })) - p.begin();
		res += p[b - 1].dis - p[a - 1].dis;
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &A);
	for(int i = 1; i <= n; i++)scanf("%d", &age[i]);
	memset(h, -1, sizeof(h));
	for(int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	calc(1);
	ll res = 0;
	while(m--)
	{
		int u, a, b;
		scanf("%d%d%d", &u, &a, &b);
		int l = (a + res) % A, r = (b + res) % A;
		if(l > r)swap(l, r);
		res = query(u, l, r);
		printf("%lld\n", res);
	}
	return 0;
}
