#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
int a[N];
int vis[N];
vector<int>eine, zwei;
priority_queue<int>q1;
priority_queue<int, vector<int>, greater<int>>q2;
int pos[N], ans[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if(a[i] & 1)eine.push_back(i), vis[i] = 1;
		else zwei.push_back(i), vis[i] = 2;
	}
	if(n & 1)
	{
		if(eine.size() > zwei.size())
		{
			for(int i = 0, j = 1; i < n / 2 + 1; i++, j++)
				pos[eine[i]] = 2 * j - 1;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 1 && i >= pos[i])q1.push(a[i]);
				if(i & 1 && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 1 && i < pos[i])q2.push(a[i]);
				if(i & 1 && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[zwei[i]] = 2 * j;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 2 && i >= pos[i])q1.push(a[i]);
				if(!(i & 1) && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 2 && i < pos[i])q2.push(a[i]);
				if(!(i & 1) && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
		}
		else
		{
			for(int i = 0, j = 1; i < n / 2 + 1; i++, j++)
				pos[zwei[i]] = 2 * j - 1;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 2 && i >= pos[i])q1.push(a[i]);
				if(i & 1 && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 2 && i < pos[i])q2.push(a[i]);
				if(i & 1 && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[eine[i]] = 2 * j;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 1 && i >= pos[i])q1.push(a[i]);
				if(!(i & 1) && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 1 && i < pos[i])q2.push(a[i]);
				if(!(i & 1) && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
		}
	}
	else
	{
		ll cost1 = 0, cost2 = 0;
		for(int i = 0; i < n / 2; i++)
		{
			int st = eine[i], ed = 2 * i + 1;
			cost1 += abs(st - ed);
			st = zwei[i], ed = 2 * i + 2;
			cost1 += abs(st - ed);
			st = eine[i], ed = 2 * i + 2;
			cost2 += abs(st - ed);
			st = zwei[i], ed = 2 * i + 1;
			cost2 += abs(st - ed);
		}
		if(cost1 <= cost2)
		{
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[eine[i]] = 2 * j - 1;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 1 && i >= pos[i])q1.push(a[i]);
				if(i & 1 && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 1 && i < pos[i])q2.push(a[i]);
				if(i & 1 && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[zwei[i]] = 2 * j;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 2 && i >= pos[i])q1.push(a[i]);
				if(!(i & 1) && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 2 && i < pos[i])q2.push(a[i]);
				if(!(i & 1) && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
		}
		else
		{
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[zwei[i]] = 2 * j - 1;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 2 && i >= pos[i])q1.push(a[i]);
				if(i & 1 && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 2 && i < pos[i])q2.push(a[i]);
				if(i & 1 && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
			for(int i = 0, j = 1; i < n / 2; i++, j++)
				pos[eine[i]] = 2 * j;
			for(int i = n; i >= 1; i--)
			{
				if(vis[i] == 1 && i >= pos[i])q1.push(a[i]);
				if(!(i & 1) && !q1.empty())
				{
					ans[i] = q1.top();
					q1.pop();
				}
			}
			for(int i = 1; i <= n; i++)
			{
				if(vis[i] == 1 && i < pos[i])q2.push(a[i]);
				if(!(i & 1) && !q2.empty())
				{
					ans[i] = q2.top();
					q2.pop();
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}