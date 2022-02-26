#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 22, M = 2010;
int n, m, a[N], ans, tot, ret;
bool tf[N], f[M];
void dp()
{
	memset(f, 0, sizeof f); f[0] = true; ans = 0; tot = 0;
	for(int i = 0; i < n; i++)
	{
		if(tf[i])continue;
		for(int j = tot; j >= 0; j--)if(f[j] && !f[j + a[i]])f[j + a[i]] = true, ans++;
		tot += a[i];
	}
	ret = max(ans, ret);
}
void dfs(int cur, int now)
{
	if(now > m)return;
	if(cur == n)
	{
		if(now == m)dp();
		return;
	}
	dfs(cur + 1, now);
	tf[cur] = true;
	dfs(cur + 1, now + 1);
	tf[cur] = false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)scanf("%d", a + i);
	dfs(0, 0);
	printf("%d\n", ret);
	return 0;
}
