#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 500010;
queue<int>q[N];
int a[M];
int ne[M];
int n, k, m;
struct cmp
{
	inline bool operator()(const int &x, const int &y)
	{
		return ne[x] < ne[y];
	}
};
priority_queue<int, vector<int>, cmp>pq;
bool vis[N];
int main()
{
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);
		q[a[i]].push(i);
	}
	for(int i = 1; i <= m; i++)
	{
		q[a[i]].pop();
		if(q[a[i]].empty())ne[i] = m + 1;
		else ne[i] = q[a[i]].front();
	}
	int ans = 0;
	for(int i = 1; i <= m; i++)
	{
		if(!vis[a[i]])
		{
			if(pq.size() == k)
			{
				vis[a[pq.top()]] = false;
				pq.pop();
			}
			pq.push(i);
			ans++;
			vis[a[i]] = true;
		}
		else
		{
			k++;
			pq.push(i);
		}
	}
	printf("%d\n", ans);
	return 0;
}
