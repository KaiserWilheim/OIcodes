#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2010, M = 1000010;
int n, m;
struct Node
{
	int x, y;
	friend bool operator < (const Node &lhs, const Node &rhs)
	{
		return (lhs.x == rhs.x) ? (lhs.y < rhs.y) : (lhs.x < rhs.x);
	}
};
Node a[N], b[N], c[N];
int sta[N], tt;
int f[M];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	for(int i = 1; i <= m; i++)
		scanf("%d%d", &c[i].x, &c[i].y);
	sort(c + 1, c + 1 + m);
	for(int i = 1; i <= m; i++)
	{
		while(tt && c[sta[tt]].x <= c[i].x && c[sta[tt]].y <= c[i].y)tt--;
		sta[++tt] = i;
	}
	m = tt;
	for(int i = 1; i <= m; i++)
		b[i] = c[sta[i]];
	int maxn = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(b[j].y < a[i].y)continue;
			maxn = max(maxn, b[j].y - a[i].y);
			f[b[j].y - a[i].y] = max(f[b[j].y - a[i].y], b[j].x - a[i].x + 1);
		}
	}
	int ans = maxn + 1;
	for(int i = maxn, j = 0; ~i; i--)
	{
		j = max(j, f[i]);
		ans = min(ans, i + j);
	}
	printf("%d\n", ans);
	return 0;
}