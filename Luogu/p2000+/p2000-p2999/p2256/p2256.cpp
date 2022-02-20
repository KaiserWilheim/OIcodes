#include <bits/stdc++.h>
using namespace std;
const int N = 20010;
map<string, int>dic;
int n, m, k;
int p[N];
int get(string s)
{
	return (*dic.find(s)).second;
}
int find(int x)
{
	if(x != p[x])
	{
		p[x] = find(p[x]);
	}
	return p[x];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		dic.insert(make_pair(s, i));
		p[i] = i;
	}
	for(int i = 1; i <= m; i++)
	{
		string a, b;
		cin >> a >> b;
		int pa = find(get(a)), pb = find(get(b));
		if(a != b)p[pa] = pb;
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++)
	{
		string a, b;
		cin >> a >> b;
		if((dic.count(a) == 0) || (dic.count(b) == 0))
		{
			puts("No.");
			continue;
		}
		int pa = find(get(a)), pb = find(get(b));
		if(pa == pb)puts("Yes.");
		else puts("No.");
	}
	return 0;
}
