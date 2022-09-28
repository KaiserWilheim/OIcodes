#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 22;
int n, m;
int v[N];
int mdep, cnta, cntb;
bool vis[1 << N];
int ans = 0;
struct Node
{
	int x, st;
};
Node a[1 << N], b[1 << N];
bool cmp1(const Node &lhs, const Node &rhs)
{
	return lhs.x < rhs.x;
}
bool cmp2(const Node &lhs, const Node &rhs)
{
	return lhs.x > rhs.x;
}
void dfs(int dep, int sum, int now, int flag)
{
	if(dep == mdep + 1)
	{
		if(!flag)a[++cnta] = { sum,now };
		else b[++cntb] = { sum,now };
		return;
	}
	dfs(dep + 1, sum, now, flag);
	dfs(dep + 1, sum + v[dep], now + (1 << (dep - 1)), flag);
	dfs(dep + 1, sum - v[dep], now + (1 << (dep - 1)), flag);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	mdep = n / 2;
	dfs(1, 0, 0, 0);
	mdep = n;
	dfs(n / 2 + 1, 0, 0, 1);
	sort(a + 1, a + 1 + cnta, cmp1);
	sort(b + 1, b + 1 + cntb, cmp2);
	int l = 1, r = 1;
	while(l <= cnta && r <= cntb)
	{
		while(-a[l].x < b[r].x && r <= cntb)r++;
		int pos = r;
		while(r <= cntb && -a[l].x == b[r].x)
		{
			if(!vis[a[l].st | b[r].st])
				vis[a[l].st | b[r].st] = true, ans++;
			r++;
		}
		if(l < cnta && a[l].x == a[l + 1].x)r = pos;
		l++;
	}
	printf("%d\n", ans - 1);
	return 0;
}