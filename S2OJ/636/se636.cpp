#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 50010;
int n, m, k;
int a[N], b[N];
bool vis[N];
struct Node
{
	int v, id;
	bool operator < (const Node &rhs)const
	{
		return v > rhs.v;
	}
};
priority_queue<Node>q1, q2;
priority_queue<int, vector<int>, greater<int> >q;
signed main()
{
	scanf("%lld%lld%lld", &n, &k, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &a[i], &b[i]);
	for(int i = 1; i <= k; i++)q.push(0);
	for(int i = 1; i <= n; i++)
	{
		q1.push({ a[i],i });
		q2.push({ b[i],i });
	}
	int ans = 0;
	while(m > 0 && ans < n)
	{
		while(q1.size() && vis[q1.top().id])q1.pop();
		while(q2.size() && vis[q2.top().id])q2.pop();
		if(q.top() + q2.top().v < q1.top().v)
		{
			m -= q2.top().v + q.top();
			if(m < 0)break;
			int id = q2.top().id;
			q.pop();
			q.push(a[id] - b[id]);
			vis[id] = true;
			q2.pop();
		}
		else
		{
			m -= q1.top().v;
			if(m < 0)break;
			vis[q1.top().id] = true;
			q1.pop();
		}
		ans++;
	}
	printf("%lld\n", ans);
	return 0;
}