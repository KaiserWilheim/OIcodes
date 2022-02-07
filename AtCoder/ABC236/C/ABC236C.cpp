#include<bits/stdc++.h>
using namespace std;
bool vis[100010];
map<string, int>dic;
int main()
{
	int n,m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		dic.insert(make_pair(s, i));
	}
	for(int i = 1; i <= m; i++)
	{
		string s;
		cin >> s;
		vis[(*dic.find(s)).second] = true;
	}
	for(int i = 1; i <= n; i++)
	{
		if(vis[i])puts("Yes");
		else puts("No");
	}
	return 0;
}
