#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
bool vis[N];
int kpd(int a, int b)
{
	return b ? kpd(b, a % b) : a;
}
int main()
{
	int d;
	scanf("%d%d%d", &n, &m, &d);
	int g = kpd(n, d);
	for(int i = 1; i <= m; i++)
	{
		int a;
		scanf("%d", &a);
		vis[a % g] = true;
	}
	int ans = 0;
	for(int i = 0; i < g; i++)
	{
		if(!vis[i])
			ans += (n / g);
	}
	printf("%d\n", ans);
	return 0;
}