#include<bits/stdc++.h>
using namespace std; 
const int N = 500010;
struct trie
{
	int s[2];
	int v, e;
}tr[N];
int idx = 0;
void build(int *u, int k)
{
	int p = 0;
	for(int i = 1; i <= k; i++)
	{
		if(tr[p].s[u[i]])
		{
			p = tr[p].s[u[i]];
		}
		else
		{
			tr[p].s[u[i]] = ++idx;
			p = idx;
		}
		tr[p].v++;
	}
	tr[p].e++;
}
int find(int *u, int k)
{
	int p = 0, res = 0;
	bool flag = false;
	for(int i = 1; i <= k; i++)
	{
		if(tr[p].s[u[i]])
		{
			p = tr[p].s[u[i]];
			res += tr[p].e;
		}
		else
		{
			flag = true;
			break;
		}
	}
	if(flag)return res;
	return res + tr[p].v - tr[p].e;
}
int main()
{
	int m, n;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int s[10010];
		int k;
		scanf("%d", &k);
		for(int i = 1; i <= k; i++)
		{
			scanf("%d", &s[i]);
		}
		build(s, k);
	}
	for(int i = 1; i <= m; i++)
	{
		int s[10010];
		int k;
		scanf("%d", &k);
		for(int i = 1; i <= k; i++)
		{
			scanf("%d", &s[i]);
		}
		int ans = find(s, k);
		printf("%d\n", ans);
	}
	return 0;
}
