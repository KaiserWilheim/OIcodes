#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;

struct trie
{
	int s[26];
	int cnt;
	int fail;
}tr[N];
int idx = 0;
int vis[N];
vector<string>dic;

void insert(string s, int id)
{
	int u = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(tr[u].s[s[i] - 'a'] != 0)u = tr[u].s[s[i] - 'a'];
		else
		{
			tr[u].s[s[i] - 'a'] = ++idx;
			u = idx;
		}
	}
	tr[u].cnt = id;
}

void get_fail()
{
	queue<int>q;
	for(int i = 0; i < 26; i++)
		if(tr[0].s[i])q.push(tr[0].s[i]);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
		{
			if(tr[u].s[i])
			{
				tr[tr[u].s[i]].fail = tr[tr[u].fail].s[i];
				q.push(tr[u].s[i]);
			}
			else
			{
				tr[u].s[i] = tr[tr[u].fail].s[i];
			}
		}
	}
}

void query(string s)
{
	int u = 0;
	for(int i = 0; i < s.length(); i++)
	{
		u = tr[u].s[s[i] - 'a'];
		for(int j = u; j > 0; j = tr[j].fail)
			vis[tr[j].cnt]++;
	}
	return;
}

void init()
{
	dic.clear();
	for(int i = 0; i <= idx; i++)
	{
		for(int j = 0; j < 26; j++)tr[i].s[j] = 0;
		tr[i].cnt = 0;
		tr[i].fail = 0;
	}
	idx = 0;
	memset(vis, 0, sizeof(vis));
}

int main()
{
	int n;
	cin >> n;
	while(n)
	{
		init();
		for(int i = 1; i <= n; i++)
		{
			string s;
			cin >> s;
			dic.push_back(s);
			insert(s, i);
		}
		get_fail();
		string t;
		cin >> t;
		query(t);
		int maxn = -1;
		for(int i = 1; i <= n; i++)
			maxn = max(maxn, vis[i]);
		cout << maxn << endl;
		for(int i = 1; i <= n; i++)
			if(vis[i] == maxn)
				cout << dic[i - 1] << endl;
		cin >> n;
	}
	return 0;
}
