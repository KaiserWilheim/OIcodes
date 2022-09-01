#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 1000010;
int n, m;
set<int>h[N];
int fa[N];
int find(int x)
{
	if(fa[x] != x)fa[x] = find(fa[x]);
	return fa[x];
}
map<pair<int, int>, int>dic;
queue<pair<int, int> >q;
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)fa[i] = i;
	for(int i = 1; i <= n * 2 - 2; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		h[u].insert(v);
		h[v].insert(u);
		dic[make_pair(u, v)]++;
		dic[make_pair(v, u)]++;
		if(dic[make_pair(u, v)] == 2)q.emplace(u, v);
	}

	while(!q.empty())
	{
		int u = q.front().first, v = q.front().second;
		q.pop();
		u = find(u), v = find(v);
		h[u].erase(v), h[v].erase(u);
		if(h[u].size() < h[v].size())swap(u, v);
		for(set<int>::iterator it = h[v].begin(); it != h[v].end(); it++)
		{
			int w = (*it);
			dic[make_pair(w, v)] = dic[make_pair(v, w)] = 0;
			h[w].erase(v), h[w].insert(u);
			dic[make_pair(w, u)]++, dic[make_pair(u, w)]++;
			if(dic[make_pair(w, u)] == 2)q.emplace(w, u);
			h[u].insert(w);
		}
		fa[v] = u;
		h[v].clear();
	}

	int tot = 0;
	for(int i = 1; i <= n; i++)
		tot += (fa[i] == i);
	puts(tot == 1 ? "YES" : "NO");
}
int main()
{
	solve();
	return 0;
}