#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
int n, k;
struct Node
{
	ll w, h;
	Node() { w = h = 0; }
	Node(ll _w, ll _h) { w = _w, h = _h; }
	bool operator < (const Node &a)const
	{
		return (w == a.w) ? (h > a.h) : (w > a.w);
	}
};
ll ans;
priority_queue<Node>q;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		ll w;
		scanf("%lld", &w);
		q.emplace(w, 1);
	}
	while((q.size() - 1) % (k - 1) != 0)
		q.emplace(0, 1);
	while(q.size() >= k)
	{
		ll h = -1, w = 0;
		for(int i = 1; i <= k; i++)
		{
			Node u = q.top();
			q.pop();
			h = max(h, u.h);
			w += u.w;
		}
		ans += w;
		q.emplace(w, h + 1);
	}
	printf("%lld\n%lld\n", ans, q.top().h - 1);
	return 0;
}
