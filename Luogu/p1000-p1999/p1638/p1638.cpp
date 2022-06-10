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
int n, k;
int vis[N];
int ans = 0x3f3f3f3f;
int main()
{
	memset(vis, -1, sizeof(vis));
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		f[i] = { i,x };
	}
	int l = 1;
	int a, b;
	int cnt = 0;
	for(int r = 1; r <= n; r++)
	{
		if(vis[f[r].id] == -1)cnt++;
		vis[f[r].id] = f[r].x;
		while(l <= r && f[l].x != vis[f[l].id])l++;
		if(cnt == k && f[r].x - f[l].x < ans)
		{
			ans = f[r].x - f[l].x;
			a = l, b = r;
		}
	}
	printf("%d %d\n", a, b);
	return 0;
}
