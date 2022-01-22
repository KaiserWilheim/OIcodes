#include <bits/stdc++.h>
using namespace std;
struct trie
{
	int next[26];
	bool visit,exist;
}name[500010];
int idx = 0;
void add(string s)
{
	int now = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(name[now].next[s[i] - 'a'] == 0)
		{
			idx++;
			name[now].next[s[i] - 'a'] = idx;
			now = idx;
		}
		else
		{
			now = name[now].next[s[i] - 'a'];
		}
	}
	name[now].exist = true;
}
void check(string s)
{
	int now = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(name[now].next[s[i] - 'a'] == 0)
		{
			puts("WRONG");
			return;
		}
		else
		{
			now = name[now].next[s[i] - 'a'];
		}
	}
	if(name[now].visit == false)
	{
		if(name[now].exist == true)
		{
			puts("OK");
			name[now].visit = true;
		}
		else
		{
			puts("WRONG");
			return;
		}
	}
	else
	{
		puts("REPEAT");
	}
}
int main()
{
	int n, m;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		string l;
		cin >> l;
		add(l);
	}
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		string p;
		cin >> p;
		check(p);
	}
	return 0;
}
