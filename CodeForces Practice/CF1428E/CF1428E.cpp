#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
ll a[N], b[N];
ll w[N];
ll f(ll x, ll y)
{
	if(y == 1)return x * x;
	ll k = x % y, w = x / y;
	ll res = k * (w + 1) * (w + 1) + (y - k) * w * w;
	return res;
}
struct Node
{
	int id;
	ll v;
	Node() { id = v = 0; }
	Node(int _i, ll _v) { id = _i, v = _v; }
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		return lhs.v < rhs.v;
	}
};
priority_queue<Node>q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		b[i] = 1;
		w[i] = f(a[i], 1);
		q.emplace(i, w[i] - f(a[i], 2));
	}
	for(int i = n + 1; i <= m; i++)
	{
		Node now = q.top();
		q.pop();
		w[now.id] = f(a[now.id], ++b[now.id]);
		q.emplace(now.id, w[now.id] - f(a[now.id], b[now.id] + 1));
	}
	ll res = 0;
	for(int i = 1; i <= n; i++)
		res += w[i];
	printf("%lld\n", res);
	return 0;
}