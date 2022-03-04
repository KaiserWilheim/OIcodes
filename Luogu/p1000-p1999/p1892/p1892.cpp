#include<bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, ans, p[N], enm[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		char opt[5];
		scanf("%s%d%d", opt, &u, &v);
		if(opt[0] == 'F')
		{
			p[find(u)] = find(v);
		}
		else
		{
			if(enm[u] == 0)enm[u] = find(v);
			else p[find(v)] = find(enm[u]);
			if(enm[v] == 0)enm[v] = find(u);
			else p[find(u)] = find(enm[v]);
		}
	}
	set<int>dic;
	for(int i = 1; i <= n; i++)
		if(!dic.count(find(i)))
			dic.insert(find(i));
	printf("%d\n", dic.size());
	return 0;
}
