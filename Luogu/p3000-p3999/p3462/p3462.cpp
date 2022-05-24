#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int a[N], b[N], num[N];
int c[40], cnt[40], tot;
bool dfs(int p)
{
	if(p > tot)return false;
	if(cnt[p])
	{
		cnt[p]--;
		return true;
	}
	if(dfs(p + 1))
	{
		cnt[p] += c[p + 1] / c[p];
		cnt[p]--;
		return true;
	}
	return false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	sort(b + 1, b + 1 + m);
	for(int i = 1; i <= m; i++)
	{
		if(b[i] != b[i - 1])c[++tot] = b[i];
		num[i] = tot;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = tot; j; j--)
		{
			cnt[j] += a[i] / c[j];
			a[i] %= c[j];
		}
	}
	for(int i = 1; i <= m; i++)
	{
		if(!dfs(num[i]))
		{
			printf("%d\n", i - 1);
			break;
		}
		if(i == m)printf("%d\n", m);
	}
	return 0;
}
