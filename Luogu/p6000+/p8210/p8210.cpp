#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, k;
int a[N];
bool vis[N];
vector<int>r[N];
int cnt;
vector<pair<int, int> >ans;
void _swap(int x, int y)
{
	ans.emplace_back(x, y);
	swap(a[x], a[y]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	a[n + 1] = n + 1, a[n + 2] = n + 2;
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			int u = i;
			while(!vis[u])
			{
				vis[u] = true;
				r[cnt].push_back(u);
				u = a[u];
			}
			++cnt;
		}
	}
	vector<int>cyc;
	for(int i = 0; i < cnt; i++)
		if(r[i].size() > 1)cyc.push_back(i);
	if(cyc.empty())
	{
		puts("0 0");
		return 0;
	}
	for(int i = cyc.size() - 1; i; i--)
		_swap(r[cyc[i]].back(), n + 2);
	_swap(r[cyc[0]].back(), n + 1);
	for(int i : r[cyc[0]])
		_swap(i, n + 2);
	_swap(r[cyc[0]].front(), n + 1);
	for(int i = 1; i < cyc.size(); i++)
		for(int j : r[cyc[i]])
			_swap(j, n + 1);
	_swap(n + 1, n + 2);
	printf("%d %d\n", 2, ans.size());
	for(auto i : ans)
		printf("%d %d\n", i.first, i.second);
	return 0;
}
