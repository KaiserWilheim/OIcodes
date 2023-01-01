#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100010;
unordered_map<int, int>dic, g[15][2];
int sta[20], pw[20];
int solve(int d, bool lim, int pre)
{
	if(!d)return dic.count(pre);
	if(g[d][lim].count(pre))return g[d][lim][pre];
	int top = lim ? sta[d] : 9;
	int res = 0;
	for(int i = 0; i <= top; i++)
		res += solve(d - 1, lim && i == top, pre + (i ? pw[i - 1] : 0));
	return g[d][lim][pre] = res;
}
int calc(int n)
{
	int tt = 0;
	while(n)
	{
		sta[++tt] = n % 10;
		n /= 10;
	}
	for(int i = 1; i <= tt; i++)g[i][0].clear(), g[i][1].clear();
	return solve(tt, 1, 0);
}
int w[20];
bool f[10][60];
void dfs(int x, int sum)
{
	if(sum > 9)return;
	if(x == 10)
	{
		int now = 0, res = 1, s = 0;
		for(int i = 1; i <= 9; i++)
			now += w[i] * pw[i - 1], s += w[i] * i;
		if(s & 1)return;
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i <= 9; i++)
			for(int k = 0; k <= w[i]; k++)
				for(int j = k * i; j <= (s >> 1); j++)
					f[i][j] |= f[i - 1][j - k * i];
		if(f[9][s >> 1])dic[now] = 1;
		return;
	}
	for(int i = 0; i <= 9 - sum; i++)w[x] = i, dfs(x + 1, sum + i);
}
int main()
{
	pw[0] = 1;
	for(int i = 1; i <= 9; i++)pw[i] = pw[i - 1] * 10;
	dfs(1, 0);
	int l, r;
	scanf("%d%d", &l, &r);
	int res = calc(r) - calc(l - 1);
	printf("%d\n", res);
	return 0;
}