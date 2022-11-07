#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
const int INF = 1e9;
int n, m;
struct Node
{
	int u, x;
	Node(int _u, int _x)
	{
		u = _u, x = _x;
	}
	bool operator < (const Node &rhs)const
	{
		return x > rhs.x;
	}
};
int a[N];
priority_queue<Node>q[N];
int idx;
vector<int>g[N];
int b[N];
vector<int>ans;
void solve(int x, int y)
{
	a[x] += y;
	ans.clear();
	while(!q[x].empty() && q[x].top().x <= a[x])
	{
		int i = q[x].top().u;
		q[x].pop();
		if(b[i] == -INF)continue;
		int sum = 0;
		for(int j : g[i])
			sum += a[j];
		if(sum >= b[i])
		{
			ans.push_back(i);
			b[i] = -INF;
		}
		else
		{
			for(int j : g[i])
			{
				int k = a[j] + (b[i] - sum - 1) / (int)g[i].size();
				q[j].emplace(i, k + 1);
			}
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	int lans = 0;
	while(m--)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int u, k;
			scanf("%d%d", &u, &k);
			u ^= lans;
			idx++;
			b[idx] = u;
			for(int i = 1; i <= k; i++)
			{
				int x;
				scanf("%d", &x);
				x ^= lans;
				q[x].emplace(idx, a[x] + (u - 1) / k + 1);
				g[idx].push_back(x);
				b[idx] += a[x];
			}
		}
		else
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u ^= lans, v ^= lans;
			solve(u, v);
			lans = ans.size();
			printf("%d", ans.size());
			sort(ans.begin(), ans.end());
			for(auto i : ans)
				printf(" %d", i);
			putchar('\n');
		}
	}
	return 0;
}
