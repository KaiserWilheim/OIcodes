#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 8000010;
int n, m;
ll sum[N], ans;
ll tr[N][2], sz[N];
int idx;
void insert(ll x)
{
	int p = 0;
	for(int i = 31; i >= 0; i--)
	{
		int c = (x >> i) & 1;
		sz[p]++;
		if(!tr[p][c])tr[p][c] = ++idx;
		p = tr[p][c];
	}
	sz[p]++;
}
ll query(ll x, int rk)
{
	int p = 0;
	ll res = 0;
	for(int i = 31; i >= 0; i--)
	{
		int c = (x >> i) & 1;
		if(!tr[p][c ^ 1])p = tr[p][c];
		else if(rk <= sz[tr[p][c ^ 1]])p = tr[p][c ^ 1], res |= (1ll << i);
		else rk -= sz[tr[p][c ^ 1]], p = tr[p][c];
	}
	return res;
}
struct Node
{
	int id, rk;
	ll w;
	Node(int _i, int _k, ll _w)
	{
		id = _i, rk = _k, w = _w;
	}
	bool operator < (const Node &rhs)const
	{
		return w < rhs.w;
	}
};
priority_queue<Node>q;
int main()
{
	scanf("%d%d", &n, &m);
	m <<= 1;
	for(int i = 1; i <= n; i++)
	{
		ll x;
		scanf("%lld", &x);
		sum[i] = sum[i - 1] ^ x;
	}
	for(int i = 0; i <= n; i++)
		insert(sum[i]);
	for(int i = 0; i <= n; i++)
		q.emplace(i, 1, query(sum[i], 1));
	for(int i = 1; i <= m; i++)
	{
		Node u = q.top();
		q.pop();
		ans += u.w;
		if(u.rk < n)q.emplace(u.id, u.rk + 1, query(sum[u.id], u.rk + 1));
	}
	printf("%lld\n", ans / 2);
	return 0;
}
