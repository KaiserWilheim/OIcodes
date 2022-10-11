#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n, m;
int a[N];
int pos[N];
struct node
{
	int l, r;
};
node p[N];
vector<int>e[N];
int find(int x)
{
	if(p[x].l != x)p[x].l = find(p[x].l);
	return p[x].l;
}
void soyuz(int a, int b)
{
	if(p[a].r == p[b].r)return;
	int fa = p[a].r, fb = p[b].r;
	if(e[fa].size() < e[fb].size())swap(fa, fb);
	for(int i : e[fb])
	{
		p[i].r = fa;
		e[fa].push_back(i);
		if(p[i - 1].r == fa)p[find(i)].l = find(i - 1);
		if(p[i + 1].r == fa)p[find(i)].l = find(i + 1);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		e[i].push_back(i);
		p[i] = { i,i };
	}
	for(int _i = 1; _i <= m; _i++)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)soyuz(l, r);
		else
		{
			if(find(l) == find(r))puts("zzy");
			else puts("orz");
		}
	}
	return 0;
}