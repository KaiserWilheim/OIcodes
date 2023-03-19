#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define ll long long
int n;
string s;
int lcs2(string x, string y)
{
	vector<vector<int>>f(x.size() + 10);
	for(auto &i : f)i.resize(y.size() + 10);
	for(int i = 1; i <= x.size(); i++)
	{
		for(int j = 1; j <= y.size(); j++)
		{
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			if(x[i - 1] == y[j - 1])f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
		}
	}
	return f[x.size()][y.size()];
}
int lcs3(string x, string y, string z)
{
	vector<vector<vector<int>>>f(x.size() + 10);
	for(auto &i : f)
	{
		i.resize(y.size() + 10);
		for(auto &j : i)j.resize(z.size() + 10);
	}
	for(int i = 1; i <= x.size(); i++)
	{
		for(int j = 1; j <= y.size(); j++)
		{
			for(int k = 1; k <= z.size(); k++)
			{
				f[i][j][k] = max({ f[i - 1][j][k],f[i][j - 1][k],f[i][j][k - 1] });
				if(x[i - 1] == y[j - 1] && y[j - 1] == z[k - 1])
					f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1] + 1);
			}
		}
	}
	return f[x.size()][y.size()][z.size()];
}
unordered_set<string>sta;
string nw;
void dfs(int u, int v)
{
	if(u == v)
	{
		sta.emplace(nw);
		return;
	}
	dfs(u + 1, v);
	nw.push_back(s[u]);
	dfs(u + 1, v);
	nw.pop_back();
}
int main()
{
	cin >> s;
	n = s.length();
	int ans = 0;
	for(int i = 1; i < n; i++)
		ans = max(ans, lcs2(s.substr(0, i), s.substr(i)) * 2);
	for(int i = 1; i < n; i++)
		for(int j = i + 1; j < n; j++)
			ans = max(ans, lcs3(s.substr(0, i), s.substr(i, j - i), s.substr(j)) * 3);
	for(int i = 0; i <= 4; i++)
		dfs(n / 5 * i, (i == 4) ? n : (n / 5 * (i + 1)));
	for(auto i : sta)
	{
		int p = 0, q = 0, cnt = 0;
		while(true)
		{
			while(q < n && s[q] != i[p])q++;
			if(q >= n)break;
			p++, q++;
			if(p == i.size())p = 0, cnt++;
		}
		if(cnt > 1)ans = max<int>(ans, i.size() * cnt);
	}
	printf("%d\n", ans);
	return 0;
}
