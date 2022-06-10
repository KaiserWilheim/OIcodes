#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010;
struct Node
{
	int x, id;
	bool operator < (const Node &a) const
	{
		return x == a.x ? id < a.id : x < a.x;
	}
}f[N];
int tot = 0;
int n, k;
int vis[N];
int ans = 0x3f3f3f3f;
int main()
{
	memset(vis, -1, sizeof(vis));
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++)
	{
		int x;
		scanf("%d", &x);
		for(int j = 1; j <= x; j++)
		{
			int c;
			scanf("%d", &c);
			f[++tot] = { c,i };
		}
	}
	sort(f + 1, f + 1 + n);
	int l = 1;
	int cnt = 0;
	for(int r = 1; r <= n; r++)
	{
		if(vis[f[r].id] == -1)cnt++;
		vis[f[r].id] = f[r].x;
		while(l <= r && f[l].x != vis[f[l].id])l++;
		if(cnt == k)
			ans = min(ans, f[r].x - f[l].x);
	}
	printf("%d\n", ans);
	return 0;
}
