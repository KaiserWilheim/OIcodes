#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int p[N], v[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
		p[i] = i;
	}
	int cnt = n;
	for(int i = 2; i <= n; i++)
	{
		if(v[i] >= v[find(i - 1)])p[i] = find(i - 1), cnt--;
	}
	while(m--)
	{
		int x, d;
		scanf("%d%d", &x, &d);
		v[x] -= d;
		if(v[x] >= v[find(x)] && p[x] != x)
		{
			printf("%d ", cnt);
			continue;
		}
		cnt++;
		for(int i = x; v[i] >= v[x] && i <= n; i++)
		{
			if(p[i] == i)cnt--;
			p[i] = x;
		}
		printf("%d ", cnt);
	}
	putchar('\n');
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}
