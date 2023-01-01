#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int N = 55, M = N << 1;
int n, m;
char s[N][N], t[N][N];
vector<pii>res;
void rotate(int x, int y)
{
	res.emplace_back(x, y);
	if(s[x][y] == 'L')
	{
		s[x][y] = s[x][y + 1] = 'U';
		s[x + 1][y] = s[x + 1][y + 1] = 'D';
	}
	else
	{
		s[x][y] = s[x + 1][y] = 'L';
		s[x][y + 1] = s[x + 1][y + 1] = 'R';
	}
}
void dfs(int x, int y)
{
	if(s[x][y] == 'L')return;
	if(s[x][y + 1] == 'L')
	{
		dfs(x + 1, y + 1);
		rotate(x, y + 1);
		rotate(x, y);
	}
	else rotate(x, y);
}
vector<pii>get()
{
	int dn = n, dm = m;
	if(m & 1)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				if(s[i][j] == 'U')t[j][i] = 'L';
				if(s[i][j] == 'D')t[j][i] = 'R';
				if(s[i][j] == 'L')t[j][i] = 'U';
				if(s[i][j] == 'R')t[j][i] = 'D';
			}
		}
		memcpy(s, t, sizeof(s));
		swap(dn, dm);
	}
	res.clear();
	for(int i = 1; i <= dn; i++)
		for(int j = 1; j <= dm; j++)
			if(s[i][j] == 'U')dfs(i, j);
	if(m & 1)
		for(int i = 0; i < res.size(); i++)
			swap(res[i].first, res[i].second);
	return res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	vector<pii>prf = get();
	for(int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	vector<pii>suf = get();
	printf("%d\n", prf.size() + suf.size());
	for(auto i : prf)
		printf("%d %d\n", i.first, i.second);
	reverse(suf.begin(), suf.end());
	for(auto i : suf)
		printf("%d %d\n", i.first, i.second);
	return 0;
}
