#include<bits/stdc++.h>
using namespace std;
const int N = 2000010;
int tot = 1, last = 1;
struct Node
{
	int len, fa;
	int s[26];
}node[N];
char str[N];
long long f[N];
long long ans;
int h[N], e[N], ne[N], idx;
void extend(int c)
{
	int p = last, np = last = ++tot;
	f[tot] = 1;
	node[np].len = node[p].len + 1;
	for(; (p) && (!node[p].s[c]); p = node[p].fa)node[p].s[c] = np;
	if(!p)
	{
		node[np].fa = 1;
	}
	else
	{
		int q = node[p].s[c];
		if(node[q].len == node[p].len + 1)
		{
			node[np].fa = q;
		}
		else
		{
			int nq = ++tot;
			node[nq] = node[q];
			node[nq].len = node[p].len + 1;
			node[q].fa = node[np].fa = nq;
			for(; (p) && (node[p].s[c] == q); p = node[p].fa)node[p].s[c] = nq;
		}
	}
	return;
}
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
	return;
}
void dfs(int u)
{
	for(int i = h[u]; ~i; i = ne[i])
	{
		dfs(e[i]);
		f[u] += f[e[i]];
	}
	if(f[u] > 1)ans = max(ans, f[u] * node[u].len);
	return;
}
int main()
{
	scanf("%s", str);
	for(int i = 0; str[i]; i++)extend(str[i] - 'a');
	memset(h, -1, sizeof(h));
	for(int i = 2; i <= tot; i++)add(node[i].fa, i);
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
