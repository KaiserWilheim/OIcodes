#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int ans[110], ori[31], idx = 0;
int from[20], to[20];
int num[10];
bool vis[10];
void dfs(int x, int d)
{
	if(vis[x])return;
	vis[x] = true;
	num[d]++;
	for(int i = 1; i <= n; i++)
	{
		if(from[i] == x)dfs(to[i], d);
	}
	//vis[x] = false;
	return;
}
void multiply(int x)
{
	for(int i = 1; i <= idx; i++)ans[i] *= x;
	for(int i = 1; i <= idx; i++)
	{
		if(ans[i] > 9)
		{
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
			if(i == idx)idx++;
		}
	}
	return;
}
int main()
{
	ans[1] = 1;
	idx = 1;
	cin >> s;
	for(int i = 0; i < s.size(); i++)ori[i + 1] = s[i] - '0';
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> from[i] >> to[i];
	}
	for(int i = 0; i <= 9; i++)
	{
		memset(vis, false, sizeof(vis));
		dfs(i, i);
	}
	for(int i = 1; i <= s.size(); i++)multiply(num[ori[i]]);
	for(int i = idx; i > 0; i--)cout << ans[i];
	putchar('\n');
	//for(int i = 0; i <= 9; i++)cout << num[i] << endl;
	return 0;
}
