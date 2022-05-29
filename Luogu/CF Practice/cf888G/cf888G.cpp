#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 6000010;
struct Trie
{
	int s[2];
}tr[N];
int idx;
void insert(int x)
{
	int p = 0;
	for(int i = 30; i >= 0; i--)
	{
		int v = (x >> i) & 1;
		if(!tr[p].s[v])tr[p].s[v] = ++idx;
		p = tr[p].s[v];
	}
}
int find(int p, int q, int x)
{
	if(x < 0)return 0;
	int a1 = -1, a2 = -1;
	if(tr[p].s[0] && tr[q].s[0])a1 = find(tr[p].s[0], tr[q].s[0], x - 1);
	if(tr[p].s[1] && tr[q].s[1])a2 = find(tr[p].s[1], tr[q].s[1], x - 1);
	if(~a1 && ~a2)return min(a1, a2);
	if(~a1)return a1;
	if(~a2)return a2;
	if(tr[p].s[1] && tr[q].s[0])a1 = find(tr[p].s[1], tr[q].s[0], x - 1) + (1 << x);
	if(tr[p].s[0] && tr[q].s[1])a2 = find(tr[p].s[0], tr[q].s[1], x - 1) + (1 << x);
	if(~a1 && ~a2)return min(a1, a2);
	if(~a1)return a1;
	if(~a2)return a2;
}
ll ans;
void dfs(int p, int x)
{
	if(x < 0)return;
	if(tr[p].s[0] && tr[p].s[1])ans += 1ll * find(tr[p].s[0], tr[p].s[1], x - 1) + (1ll << x);
	if(tr[p].s[0])dfs(tr[p].s[0], x - 1);
	if(tr[p].s[1])dfs(tr[p].s[1], x - 1);
}
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		insert(x);
	}
	dfs(0, 30);
	printf("%lld\n", ans);
	return 0; 
}
