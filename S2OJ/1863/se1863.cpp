#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1000010, M = 2010;
int n, m, k;
char s[N];
int cnt[M][M];
int calc(int l, int t, int r, int b)
{
	return cnt[r][b] - cnt[l - 1][b] - cnt[r][t - 1] + cnt[l - 1][t - 1];
}
set<pair<int, int>>sta;
void solve()
{
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", s + 1);
	int row = 0, col = 0, u = 0, d = 0, l = 0, r = 0, x = 0, y = 0;
	sta.clear();
	sta.emplace(x, y);
	for(int i = 1; s[i]; i++)
	{
		if(s[i] == 'U')row--, x--;
		if(s[i] == 'D')row++, x++;
		if(s[i] == 'L')col--, y--;
		if(s[i] == 'R')col++, y++;
		sta.emplace(x, y);
		u = max(u, row), d = max(d, -row);
		l = max(l, col), r = max(r, -col);
	}
	d = n - d, r = m - r, u++, l++;
	if(u > d || l > r)
	{
		if(k == 0)printf("%d\n", n * m);
		else puts("0");
		return;
	}
	for(int i = 0; i <= 2 * n + 1; i++)
		for(int j = 0; j <= 2 * m + 1; j++)
			cnt[i][j] = 0;
	for(auto i : sta)
	{
		int x = i.first, y = i.second;
		if(abs(x) > n || abs(y) > m)continue;
		cnt[x + n + 1][y + m + 1]++;
	}
	for(int i = 0; i <= 2 * n + 1; i++)
		for(int j = 0; j <= 2 * m + 1; j++)
			cnt[i][j] += cnt[i][j - 1];
	for(int j = 0; j <= 2 * m + 1; j++)
		for(int i = 0; i <= 2 * n + 1; i++)
			cnt[i][j] += cnt[i - 1][j];
	int res = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(calc(u - i + n + 1, l - j + m + 1, d - i + n + 1, r - j + m + 1) == (d - u + 1) * (r - l + 1) - k)res++;
	printf("%d\n", res);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
