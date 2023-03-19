#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 410;
const int mod = 1e9 + 7;
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int n, m;
char s[N], t[N];
int f[N][N][N];
int dfs(int i, int j, int k, int l)
{
	if(i > n)return j == m && !k && !l;
	if(~f[i][j][k])return f[i][j][k];
	int res = 0;
	if(s[i] == '-')
	{
		if(k)res = add(res, dfs(i + 1, j, k - 1, l));
		if(l)res = add(res, dfs(i + 1, j, k, l - 1));
	}
	else
	{
		res = dfs(i + 1, j, k, l + 1);
		if(!j && !l)res = add(res, dfs(i + 1, 0, k + 1, 0));
		if(s[i] == t[j + 1] && !l)res = add(res, dfs(i + 1, j + 1, k, 0));
	}
	return f[i][j][k] = res;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		scanf("%s", s + 1);
		scanf("%s", t + 1);
		int tot = 0;
		for(int i = 1; i <= n; i++)
			tot += (s[i] == '-') ? -1 : 1;
		if(tot != m)
		{
			puts("0");
			continue;
		}
		memset(f, -1, sizeof(f));
		printf("%d\n", dfs(1, 0, 0, 0));
	}
	return 0;
}
