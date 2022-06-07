#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 400010;
int n, m, K;
int fa[N], des[N], vis[N], ans[N], cnt;
struct Edge
{
	int x, y, c;
	bool operator <(const Edge b)const
	{
		return c < b.c;
	}
}a[N];
int read()
{
	int ret = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch>'9') { if(ch == '-') f = -f; ch = getchar(); }
	while(ch >= '0' && ch <= '9') ret = ret * 10 + ch - 48, ch = getchar();
	return ret * f;
}
int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if(fx != fy) fa[fx] = fy, cnt--;
}
int main()
{
	n = read(), m = read();
	cnt = n;
	for(int i = 0; i < n; i++)
		fa[i] = i;
	for(int i = 1; i <= m; i++)
		a[i] = { read(),read(),0 };
	K = read();
	for(int i = 1; i <= K; i++)
		vis[des[i] = read()] = K - i + 1;
	for(int i = 1; i <= m; i++)
		a[i].c = max(vis[a[i].x], vis[a[i].y]);
	sort(a + 1, a + 1 + m);
	for(int i = 0, j = 1; i <= K; i++)
	{
		for(; a[j].c == i; j++)
			merge(a[j].x, a[j].y);
		ans[i] = cnt - (K - i);
	}
	for(int i = K; i >= 0; i--) printf("%d\n", ans[i]);
	return 0;
}
