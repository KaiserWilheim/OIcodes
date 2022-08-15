#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
int a[N], b[N];
void solve()
{
	scanf("%d", &n);
	int maxn = 0;
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		maxn = max(maxn, a[i] - b[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		if(a[i] - b[i] < maxn && b[i] != 0)
		{
			puts("NO");
			return;
		}
	}
	puts("YES");
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
