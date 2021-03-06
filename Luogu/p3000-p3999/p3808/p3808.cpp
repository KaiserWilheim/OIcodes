#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;

struct trie
{
	int s[26];
	int cnt;
	int fail;
}tr[N];
int idx = 0;

void insert(string s)
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
	tr[u].cnt++;
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

int query(string s)
{
	int u = 0;
	int res = 0;
	for(int i = 0; i < s.length(); i++)
	{
		u = tr[u].s[s[i] - 'a'];
		for(int j = u; j > 0 && tr[j].cnt > 0; j = tr[j].fail)
		{
			res += tr[j].cnt;
			tr[j].cnt = 0;
		}
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		insert(s);
	}
	get_fail();
	string t;
	cin >> t;
	cout << query(t) << endl;
	return 0;
}
