#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010;
int n, m;
int X;
struct circ
{
	int x, y, r, w;
	bool operator < (const circ &rhs)const
	{
		return r < rhs.r;
	}
};
circ c[N];
struct hcirc
{
	int x, id, op;
	bool operator < (const hcirc &rhs)const
	{
		if(x == rhs.x) return op > rhs.op;
		return x < rhs.x;
	}
};
hcirc hc[N];
int tot;
vector<int>e[N];
double get(int id, int op)
{
	double d = sqrt(c[id].r * c[id].r - (X - c[id].x) * (X - c[id].x));
	if(!op)return 1.0 * c[id].y + d;
	else return 1.0 * c[id].y - d;
}
struct Node
{
	int id, op;
	Node() {}
	Node(int _i, int _o)
	{
		id = _i, op = _o;
	}
	bool operator < (const Node &rhs)const
	{
		return get(id, op) > get(rhs.id, rhs.op);
	}
};
multiset<Node>s;
int f[N][2];
void dfs(int p)
{
	f[p][0] = f[p][1] = 0;
	for(int v : e[p])
	{
		dfs(v);
		f[p][1] += max(f[v][0], f[v][1]);
		f[p][0] += f[v][0];
	}
	f[p][1] = max(f[p][1], f[p][0] + c[p].w);
}
int fa[N];
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld%lld", &c[i].x, &c[i].y, &c[i].r, &c[i].w);
		hc[++tot] = { c[i].x - c[i].r,i,0 };
		hc[++tot] = { c[i].x + c[i].r,i,1 };
	}
	sort(hc + 1, hc + 1 + tot);
	for(int i = 1; i <= tot; i++)
	{
		int id = hc[i].id;
		if(!hc[i].op)
		{
			X = hc[i].x;
			s.emplace(id, 0);
			auto pos = s.lower_bound({ id,0 });
			if(pos != s.begin())
			{
				pos--;
				Node pre = *pos;
				if(!pre.op)fa[id] = pre.id;
				else fa[id] = fa[pre.id];
			}
			s.emplace(id, 1);
		}
		else
		{
			s.erase(s.find({ id,0 }));
			s.erase(s.find({ id,1 }));
		}
	}
	for(int i = 1; i <= n; i++)
		e[fa[i]].push_back(i);
	dfs(0);
	printf("%lld\n", max(f[0][0], f[0][1]));
	return 0;
}