#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
int a[N], pos[N];
int res[N];
bool vis[N];
priority_queue<int, vector<int>, greater<int>>q;
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		vis[i] = false;
	while(!q.empty())q.pop();
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		vis[a[i]] = true;
		pos[a[i]] = i;
	}
	int del = n;
	res[n + 1] = 1e9;
	for(int i = n; i >= 1; i--)
		res[i] = min(res[i + 1], (a[i] > 0 ? a[i] : int(1e9)));
	for(int i = 1; i <= n; i++)
		if(!vis[i])q.push(i);
	for(int i = 1; i < n; i++)
	{
		if(a[i] == 0)
		{
			if(res[i] > q.top())
			{
				a[i] = q.top();
				q.pop();
			}
			else
			{
				a[i] = res[i];
				del = pos[res[i]];
				break;
			}
		}
		else if(a[i + 1] != 0)
		{
			if(a[i] > a[i + 1])
			{
				del = i;
				q.push(a[i]);
				break;
			}
		}
		else
		{
			if(a[i] > q.top())
			{
				del = i;
				q.push(a[i]);
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(i == del || a[i] != 0)continue;
		a[i] = q.top();
		q.pop();
	}
	for(int i = 1; i <= n; i++)
	{
		if(i == del)continue;
		printf("%d ", a[i]);
	}
	putchar('\n');
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}