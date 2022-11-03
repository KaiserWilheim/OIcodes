#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
struct Node
{
	int s[26];
	int fail;
	int cnt, sum;
};
Node tr[N];
int idx;
int pos[N], vis[N], cnt;
vector<int>e[N];
void insert(string s, int id)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(tr[p].s[s[i] - 'a'] != 0)p = tr[p].s[s[i] - 'a'];
		else
		{
			tr[p].s[s[i] - 'a'] = ++idx;
			p = idx;
		}
	}
	if(!tr[p].cnt)tr[p].cnt = ++cnt;
	pos[id] = tr[p].cnt;
}
void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 26; i++)
		if(tr[0].s[i])q.push(tr[0].s[i]);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
		{
			if(tr[p].s[i])
			{
				tr[tr[p].s[i]].fail = tr[tr[p].fail].s[i];
				q.push(tr[p].s[i]);
			}
			else
			{
				tr[p].s[i] = tr[tr[p].fail].s[i];
			}
		}
		e[tr[p].fail].push_back(p);
	}
}
void query(string s)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
	{
		p = tr[p].s[s[i] - 'a'];
		tr[p].sum++;
	}
}
void dfs(int p)
{
	if(e[p].empty())
	{
		if(tr[p].cnt)vis[tr[p].cnt] = tr[p].sum;
		return;
	}
	for(int i : e[p])
	{
		dfs(i);
		tr[p].sum += tr[i].sum;
	}
	if(tr[p].cnt)vis[tr[p].cnt] = tr[p].sum;
}
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		insert(s, i);
	}
	get_fail();
	string t;
	cin >> t;
	query(t);
	dfs(0);
	for(int i = 1; i <= n; i++)
		cout << vis[pos[i]] << endl;
	return 0;
}