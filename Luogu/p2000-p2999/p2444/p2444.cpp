#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n, m;
struct Node
{
	int c[2];
	int fail;
	bool tag;
};
Node tr[N << 1];
int idx;
void insert(string s)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(tr[p].c[s[i] - '0'] != 0)p = tr[p].c[s[i] - '0'];
		else
		{
			tr[p].c[s[i] - '0'] = ++idx;
			p = idx;
		}
	}
	tr[p].tag = true;
}
void getFail()
{
	queue<int>q;
	for(int i = 0; i <= 1; i++)
		if(tr[0].c[i])q.push(tr[0].c[i]);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		int f = tr[p].fail;
		for(int i = 0; i <= 1; i++)
		{
			if(tr[p].c[i])
			{
				tr[tr[p].c[i]].fail = tr[f].c[i];
				tr[tr[p].c[i]].tag |= tr[tr[f].c[i]].tag;
				q.push(tr[p].c[i]);
			}
			else
			{
				tr[p].c[i] = tr[f].c[i];
			}
		}
	}
}
bool vis[N], done[N];
void dfs(int p)
{
	vis[p] = true;
	for(int i = 0; i <= 1; i++)
	{
		if(vis[tr[p].c[i]])
		{
			puts("TAK");
			exit(0);
		}
		if(!tr[tr[p].c[i]].tag && !done[tr[p].c[i]])
		{
			done[tr[p].c[i]] = true;
			dfs(tr[p].c[i]);
		}
	}
	vis[p] = false;
}
string s[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		cin >> s[i];
		insert(s[i]);
	}
	getFail();
	dfs(0);
	puts("NIE");
	return 0;
}