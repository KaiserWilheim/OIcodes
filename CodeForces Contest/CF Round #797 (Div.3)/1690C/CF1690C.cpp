#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n;
int s[N], f[N];
int d[N];
void solve()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &s[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &f[i]);
	int now = 0;
	for(int i = 1; i <= n; i++)
	{
		if(now <= s[i])
		{
			d[i] = f[i] - s[i];
			now = f[i];
		}
		else
		{
			d[i] = f[i] - now;
			now = f[i];
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", d[i]);
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
