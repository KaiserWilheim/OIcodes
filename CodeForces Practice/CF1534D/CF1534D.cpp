#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010;
int n;
bool vis[N];
int fa[N];
int dis[N];
set<pair<int, int>>e;
int main()
{
	cin >> n;
	cout << "? " << 1 << endl;
	for(int i = 1; i <= n; i++)
		cin >> dis[i];
	int cnt0 = 0, cnt1 = 0;
	for(int i = 2; i <= n; i++)
	{
		if(dis[i] & 1)cnt1++;
		else cnt0++;
		if(dis[i] == 1)
			e.emplace(1, i);
	}
	queue<int>q;
	if(cnt1 > cnt0)
	{
		for(int i = 2; i <= n; i++)
			if(dis[i] % 2 == 0)q.push(i);
	}
	else
	{
		for(int i = 2; i <= n; i++)
			if(dis[i] & 1)q.push(i);
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		cout << "? " << u << endl;
		for(int i = 1; i <= n; i++)
			cin >> dis[i];
		for(int i = 1; i <= n; i++)
			if(dis[i] == 1)
				e.emplace(min(u, i), max(u, i));
	}
	cout << "!" << endl;
	for(auto i : e)
		cout << i.first << " " << i.second << endl;
	return 0;
}