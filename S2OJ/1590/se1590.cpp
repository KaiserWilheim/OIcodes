#include<bits/stdc++.h>
#include<bitset>
using namespace std;
#define ll long long
const int N = 5010;
int n, m;
bitset<N>e[N], f[N];
bitset<N>vis;
int dis[N], far[N];
int bfs(int s)
{
	int res = 0;
	queue<int>q;
	vis.set();
	vis.flip(s);
	dis[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		bitset<N> h = e[u] & vis;
		for(int i = h._Find_first(); i != h.size(); i = h._Find_next(i))
		{
			dis[i] = dis[u] + 1;
			res = max(res, dis[i]);
			q.push(i);
			vis.flip(i);
		}
	}
	return res;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		char s[N];
		cin >> s + 1;
		for(int j = i + 1; j <= n; j++)
			if(s[j] == '1')e[i].flip(j), e[j].flip(i);
	}
	int minn = INT_MAX, minp = 0, minq = 0;
	for(int i = 1; i <= n; i++)
	{
		far[i] = bfs(i);
		if(far[i] < minn)minn = far[i], minp = i;
		for(int j = 1; j <= n; j++)
			if(dis[j] == far[i])f[i].flip(j);
	}
	queue<int>q;
	vis.set();
	for(int i = 1; i <= n; i++)
	{
		if(far[i] == minn)
		{
			for(int j = i + 1; j <= n; j++)
			{
				if(far[j] == minn && e[i][j] && (f[i] & f[j]).none())
				{
					minp = i, minq = j;
					break;
				}
			}
		}
		if(minq != 0)break;
	}
	vis.flip(minp);
	q.push(minp);
	if(minq != 0)
	{
		vis.flip(minq);
		q.push(minq);
		printf("%d %d\n", minp, minq);
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		bitset<N> h = e[u] & vis;
		for(int i = h._Find_first(); i != h.size(); i = h._Find_next(i))
		{
			printf("%d %d\n", u, i);
			q.push(i);
			vis.flip(i);
		}
	}
	return 0;
}