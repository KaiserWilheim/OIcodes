#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n, k;
struct Range
{
	int l, r;
	ll w;
};
bool cmpw(const Range &lhs, const Range &rhs)
{
	return lhs.w > rhs.w;
}
Range a[N];
int x[N];
vector<Range>h[N];
ll f[N];
ll tot, sum;
priority_queue<int, vector<int>, greater<int>>q;
void push(ll x)
{
	if(q.size() < k)
	{
		q.push(x);
		sum += x;
	}
	else if(x > q.top())
	{
		sum += x - q.top();
		q.pop();
		q.push(x);
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int l, r; ll w;
		scanf("%d%d%lld", &l, &r, &w);
		x[i * 2 - 1] = l, x[i * 2] = r;
		a[i] = { l,r,w };
		tot += w;
	}
	int m = 2 * n;
	sort(x + 1, x + 1 + m);
	m = unique(x + 1, x + 1 + m) - x - 1;
	for(int i = 1; i <= n; i++)
	{
		a[i].l = lower_bound(x + 1, x + 1 + m, a[i].l) - x;
		a[i].r = lower_bound(x + 1, x + 1 + m, a[i].r) - x;
		h[a[i].l].push_back(a[i]);
	}
	f[0] = 0;
	for(int i = 1; i <= m; i++)
	{
		while(!q.empty())q.pop();
		sum = 0;
		for(int j = i; j >= 1; j--)
		{
			for(auto x : h[j])
				if(x.r <= i)push(x.w);
			f[i] = max(f[i], f[j - 1] + sum);
		}
	}
	printf("%lld\n", tot - f[m]);
	return 0;
}