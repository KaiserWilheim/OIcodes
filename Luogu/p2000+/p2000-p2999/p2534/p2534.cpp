#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 50;
int n, a[MAXN + 5], b[MAXN + 5];
bool sol;
inline int h()
{
	int cnt = 0;
	for(int i = 1; i <= n; ++i)
		cnt += abs(a[i] - a[i + 1]) != 1;
	return cnt;
}

void dfs(int g, int f, int pre)
{
	if((sol) || (g + h() > f)) return;
	if(!h())
	{
		sol = 1;
		return;
	}
	for(int i = 1; i <= n; ++i)
	{
		if(i == pre) continue;
		reverse(a + 1, a + i + 1);
		dfs(g + 1, f, i);
		reverse(a + 1, a + i + 1);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
	a[n + 1] = n + 1;
	for(int i = 0; ; ++i)
	{
		sol = false;
		dfs(0, i, 0);
		if(sol)
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
