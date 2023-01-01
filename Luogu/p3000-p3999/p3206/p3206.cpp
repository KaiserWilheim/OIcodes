#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010, M = 20010;
int n, m, ask;
struct DSU
{
	int p[M];
	int sz[M];
	struct op { int u, v; };
	op sta[N]; int tt;
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
			p[i] = i, sz[i] = 1;
		tt = 0;
	}
	int find(int x)
	{
		if(p[x] != x)return find(p[x]);
		return x;
	}
	void soyuz(int a, int b)
	{
		int fa = find(a), fb = find(b);
		if(fa == fb)return;
		if(sz[fa] < sz[fb])swap(fa, fb);
		sz[fa] += sz[fb];
		p[fb] = fa;
		sta[++tt] = { fa,fb };
	}
	void undo()
	{
		op now = sta[tt--];
		p[now.v] = now.v;
		sz[now.u] -= sz[now.v];
	}
	void clear(int lim)
	{
		while(tt > lim)undo();
	}
};
DSU s, s1;
struct Edge
{
	int u, v;
	ll w;
	int tag;
	friend bool operator < (const Edge &lhs, const Edge &rhs)
	{
		return lhs.w < rhs.w;
	}
};
Edge e[N];
bool book[N];
struct Moved
{
	int u, v;
};
struct Query
{
	int num;
	ll val;
	ll ans;
};
Query q[N];
vector<Edge>v[30];
vector<Moved>vq;
vector<Edge>tr;
ll res[30];
int tim[30];
void pushdown(int dep)
{
	tr.clear();
	for(int i = 0; i < v[dep].size(); i++)
		tr.push_back(v[dep][i]);
	sort(tr.begin(), tr.end());
	for(int i = 0; i < tr.size(); i++)
	{
		if(s1.find(tr[i].u) == s1.find(tr[i].v))
		{
			tr[i].tag = -1;
			continue;
		}
		s1.soyuz(tr[i].u, tr[i].v);
	}
	s1.clear(0);
	res[dep + 1] = res[dep];
	for(int i = 0; i < vq.size(); i++)
		s1.soyuz(vq[i].u, vq[i].v);
	vq.clear();
	for(int i = 0; i < tr.size(); i++)
	{
		if(tr[i].tag == -1 || s1.find(tr[i].u) == s1.find(tr[i].v))continue;
		tr[i].tag = 1;
		s1.soyuz(tr[i].u, tr[i].v);
		s.soyuz(tr[i].u, tr[i].v);
		res[dep + 1] += tr[i].w;
	}
	s1.clear(0);
	v[dep + 1].clear();
	for(int i = 0; i < tr.size(); i++)
	{
		if(tr[i].tag != 0)continue;
		Edge now;
		now.u = s.find(tr[i].u);
		now.v = s.find(tr[i].v);
		if(now.u == now.v)continue;
		now.w = tr[i].w;
		now.tag = 0;
		v[dep + 1].push_back(now);
	}
	return;
}
void solve(int l, int r, int dep)
{
	tim[dep] = s.tt;
	int mid = (l + r) >> 1;
	if(r - l == 1)
	{
		Edge now;
		now.u = s.find(e[q[r].num].u);
		now.v = s.find(e[q[r].num].v);
		now.w = q[r].val;
		e[q[r].num].w = q[r].val;
		now.tag = 0;
		v[dep].push_back(now);
		pushdown(dep);
		q[r].ans = res[dep + 1];
		s.clear(tim[dep - 1]);
		return;
	}
	for(int i = l + 1; i <= mid; i++)
		book[q[i].num] = true;
	for(int i = mid + 1; i <= r; i++)
	{
		if(book[q[i].num])continue;
		Edge now;
		now.u = s.find(e[q[i].num].u);
		now.v = s.find(e[q[i].num].v);
		now.w = e[q[i].num].w;
		now.tag = 0;
		v[dep].push_back(now);
	}
	for(int i = l + 1; i <= mid; i++)
	{
		Moved now;
		now.u = s.find(e[q[i].num].u);
		now.v = s.find(e[q[i].num].v);
		vq.push_back(now);
	}
	pushdown(dep);
	for(int i = mid + 1; i <= r; i++)
	{
		if(book[q[i].num])continue;
		v[dep].pop_back();
	}
	for(int i = l + 1; i <= mid; i++)
		book[q[i].num] = false;
	solve(l, mid, dep + 1);
	for(int i = 0; i < v[dep].size(); i++)
		v[dep][i].tag = 0;
	for(int i = mid + 1; i <= r; i++)
		book[q[i].num] = true;
	for(int i = l + 1; i <= mid; i++)
	{
		if(book[q[i].num])continue;
		Edge now;
		now.u = s.find(e[q[i].num].u);
		now.v = s.find(e[q[i].num].v);
		now.w = e[q[i].num].w;
		now.tag = 0;
		v[dep].push_back(now);
	}
	for(int i = mid + 1; i <= r; i++)
	{
		book[q[i].num] = false;
		Moved now;
		now.u = s.find(e[q[i].num].u);
		now.v = s.find(e[q[i].num].v);
		vq.push_back(now);
	}
	pushdown(dep);
	solve(mid, r, dep + 1);
	s.clear(tim[dep - 1]);
	return;
}
int main()
{
	scanf("%d%d%d", &n, &m, &ask);
	s.init(n), s1.init(n);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
	for(int i = 1; i <= ask; i++)
		scanf("%d%lld", &q[i].num, &q[i].val);
	for(int i = 1; i <= ask; i++)
	{
		book[q[i].num] = true;
		Moved now;
		now.u = e[q[i].num].u, now.v = e[q[i].num].v;
		vq.push_back(now);
	}
	for(int i = 1; i <= m; i++)
	{
		if(book[i])continue;
		v[1].push_back(e[i]);
	}
	for(int i = 1; i <= ask; i++)
		book[q[i].num] = false;
	solve(0, ask, 1);
	for(int i = 1; i <= ask; i++)
		printf("%lld\n", q[i].ans);
	return 0;
}
